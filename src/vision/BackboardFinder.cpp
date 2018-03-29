#include "BackboardFinder.h"
//#include "BetterBinaryImage.h"
#include <math.h>
#include "WPILib.h"
#include "iostream"



BackboardFinder::BackboardFinder() : VisionProcess() {

  printf("Starting Camera\n\n\n\n\n\n\n");
  width_ = 0;
  vDiff_ = 0;

  useTopForWidth_ = false;

  useSkew_ = true;
}



double BackboardFinder::GetHDiff() {
  return width_;
}
double BackboardFinder::GetVDiff() {
  return vDiff_;
}

bool BackboardFinder::SeesTarget() {
  return HasFreshTarget() && seesTarget_;
}

double BackboardFinder::GetX() {
  if (-1.0 <= x_ && x_ <= 1.0) {
    return x_;
  } else {
    return 0;
  }
}

double BackboardFinder::GetDistance() {
  double w = width_;
  if (useTopForWidth_) {
    w += 7; // difference between target width and side to side distance
  }
  return 3.512162035166973e-10 * pow(width_, 6) +
		  -2.499565619933737e-07 * pow(width_, 5) +
		  7.249335506446627e-05 * pow(width_, 4) +
		  -0.010982102151858 * pow(width_, 3) +
		  0.925726454960144 * pow(width_, 2) +
		  9.943136608058143e+02 * width_ + 9.943136608058143e+02;
}
/*
double BackboardFinder::GetAngle() {
  //normalized x location (-1 to 1) times the pixels along
  //that one side = number of pixels off
  //47/320 = degree/pixel based on fov/horizontal resolution
  //pixels * degrees / pixels = degrees
  //printf("get: %f\n", (float) GetX());
  double offset = 0.0; //0.0
  double ret = GetX() * 160.0 * 47.0 / 320.0 + offset;
  if (useSkew_) {
    ret += (orientation_ * 2.0 / 18.0);
  }
  return ret;
 // std::cout << " Rough Angle: " << ret << "\n";

}
*/
void BackboardFinder::SetUseSkew(bool useSkew) {
  useSkew_ = useSkew;
}

void BackboardFinder::DoVision() {
  // Get image from camera
  AxisCamera &camera = AxisCamera::GetInstance("10.13.19.20");
  ColorImage img(IMAQ_IMAGE_RGB);
  if (!camera.GetImage(&img))
    return;
  //

  // RGB Threshold -> BinaryImage
  BinaryImage* bimg = img.ThresholdRGB((int)0, (int)115,
                                       (int)125, (int)255,
                                       (int)0, (int)185);

  // take out small things
  Image* image = bimg->GetImaqImage();
  if (!image)
    return;
  int pKernel[9] = {1,1,1,1,1,1,1,1,1};
  StructuringElement structElem;
  structElem.matrixCols = 3;
  structElem.matrixRows = 3;
  structElem.hexa = FALSE;
  structElem.kernel = pKernel;

  // Filters particles based on their size.
  imaqSizeFilter(image, image, TRUE, 1, IMAQ_KEEP_LARGE, &structElem);

  // Convex Hull
  imaqConvexHull(image, image, true);

  // Convex Hull Perimeter, pParamter = perimeter Paramater
  int pParameter[1] = {20};
  double pLower[1] = {0};
  double pUpper[1] = {100};
  int pCalibrated[1] = {0};
  int pExclude[1] = {0};

  ParticleFilterCriteria2* pParticleCriteria = NULL;
  ParticleFilterOptions pParticleFilterOptions;
  int pNumParticles;


  pParticleCriteria = (ParticleFilterCriteria2*)malloc(sizeof(ParticleFilterCriteria2));
  pParticleCriteria[0].parameter = (MeasurementType)pParameter[0];
  pParticleCriteria[0].lower = pLower[0];
  pParticleCriteria[0].upper = pUpper[0];
  pParticleCriteria[0].calibrated = pCalibrated[0];
  pParticleCriteria[0].exclude = pExclude[0];

  pParticleFilterOptions.rejectMatches = TRUE;
  pParticleFilterOptions.rejectBorder = 0;
  pParticleFilterOptions.connectivity8 = TRUE;
  imaqParticleFilter3(image, image, pParticleCriteria, 1, &pParticleFilterOptions, NULL, &pNumParticles);
  free(pParticleCriteria);

  // Filter based on squarishness, eParamter = elongationParamter
  int eParameter =  53;
  double eLower = 1.2;
  double eUpper = 2.7;
  int eCalibrated = 0;
  int eExclude = 0;
  ParticleFilterCriteria2* eParticleCriteria = NULL;
  ParticleFilterOptions eParticleFilterOptions;
  int eNumParticles;
  eParticleCriteria = (ParticleFilterCriteria2*)malloc(sizeof(ParticleFilterCriteria2));

  eParticleCriteria[0].parameter = (MeasurementType) eParameter;
  eParticleCriteria[0].lower = eLower;
  eParticleCriteria[0].upper = eUpper;
  eParticleCriteria[0].calibrated = eCalibrated;
  eParticleCriteria[0].exclude = eExclude;

  eParticleFilterOptions.rejectMatches = FALSE;
  eParticleFilterOptions.rejectBorder = 0;
  eParticleFilterOptions.connectivity8 = TRUE;
  imaqParticleFilter3(image, image, eParticleCriteria, 1, &eParticleFilterOptions, NULL, &eNumParticles);
  free(eParticleCriteria);

  // Extract Particles (4?)
  ParticleAnalysisReport top;
  vector<ParticleAnalysisReport>* particles = new vector<ParticleAnalysisReport>;
  int particleCount = bimg->GetNumberParticles();
  for(int particleIndex = 0; particleIndex < particleCount; particleIndex++) {
    particles->push_back(bimg->GetParticleAnalysisReport(particleIndex));
  }

  // Find top target
  int topIndex = 0;
  for (int i = 0; i < particles->size(); i++) {
    ParticleAnalysisReport p = (*particles)[i];
    if (i == 0){
      top = p;
    }
    if (p.center_mass_y_normalized < top.center_mass_y_normalized) {
      top = p;
      topIndex = i;
    }
  }


  // Skew of target gives us our lateral position on the field
 /* double orientation =0;
  int comx = 0;
  if (particles->size() >=1 ) {
    bimg->ParticleMeasurement(topIndex, IMAQ_MT_ORIENTATION, &orientation);
    bimg->ParticleMeasurement(topIndex, IMAQ_MT_CENTER_OF_MASS_X, &comx);
  } else {
    orientation = 0;
  }

  if (orientation > 90) {
    orientation -= 180;
  }
  orientation_ = orientation;
*/
  // Calculate x offset from target center

  seesTarget_ = (particles->size() >= 1) && particles->size() < 5;
   x_ = seesTarget_ ? top.center_mass_x_normalized : 0.0;


	std::cout << " TargetLocked?: " << seesTarget_ << "\n";//", X Offset:" << x_ << "\n";


  // Calculate angle on field based on ?
  width_ = top.boundingRect.width;

  delete bimg;
  lastUpdate_ = Timer::GetFPGATimestamp();
}


bool BackboardFinder::HasFreshTarget() {
  return (Timer::GetFPGATimestamp() - lastUpdate_ < .5); // 500ms
}

bool BackboardFinder::HasLock() {
	if(seesTarget_ == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

