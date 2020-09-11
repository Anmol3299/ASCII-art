#include <array>
#include <opencv2/opencv.hpp>
#include <string>
#include <string_view>
#include <vector>

static constexpr float MAX_PIXEL_VALUE = 255;
static constexpr std::string_view ascii_chars{
    "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"
};

using pixelMat = std::vector<std::vector<std::array<uint16_t, 3>>>;
using intensityMat = std::vector<std::vector<float>>;

pixelMat getPixelMatrix(std::string const& img_loc);
intensityMat getIntensityMatrix(pixelMat const& pixel_mat,
                                std::string const& algo_name = "average");
intensityMat normalizeIntensityMatrix(intensityMat intensity_mat) noexcept;
intensityMat invertIntensityMat(intensityMat intensity_mat) noexcept;
void printAsciiImage(intensityMat const& normalized_mat) noexcept;
