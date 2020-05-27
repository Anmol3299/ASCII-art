#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

static constexpr float MAX_PIXEL_VALUE = 255;
static std::string const ascii_chars = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

typedef std::vector<std::vector<cv::Vec<uint16_t, 3>>> pixelMat;
typedef std::vector<std::vector<float>> intensityMat;

pixelMat getPixelMatrix(std::string const& img_loc);
intensityMat getIntensityMatrix(pixelMat const& pixel_mat,
                                std::string algo_name = "average");
intensityMat normalizeIntensityMatrix(intensityMat intensity_mat);
intensityMat invertIntensityMat(intensityMat intensity_mat);
void printAsciiImage(intensityMat const& normalized_mat);
