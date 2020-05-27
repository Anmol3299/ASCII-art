#include "image_ops.hpp"
#include <stdexcept>

pixelMat getPixelMatrix(std::string const& img_loc)
{
    cv::Mat img = cv::imread(img_loc);
    if (img.empty()) {
        throw std::runtime_error(std::string("Not a valid image file."));
    }

    auto height = img.rows;
    auto width = img.cols;
    pixelMat pixel_mat(height, std::vector<cv::Vec<uint16_t, 3>>(width));
    uint8_t* pixel_ptr = (uint8_t*)img.data;
    int cn = img.channels();
    for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
            uint16_t R = pixel_ptr[i * img.cols * cn + j * cn + 2];
            uint16_t G = pixel_ptr[i * img.cols * cn + j * cn + 1];
            uint16_t B = pixel_ptr[i * img.cols * cn + j * cn + 0];
            pixel_mat[i][j][0] = R;
            pixel_mat[i][j][1] = G;
            pixel_mat[i][j][2] = B;
        }
    }

    return pixel_mat;
}

intensityMat getIntensityMatrix(pixelMat const& pixel_mat,
                                std::string algo_name)
{
    auto height = pixel_mat.size();
    auto width = pixel_mat[0].size();
    intensityMat intensity_mat(height, std::vector<float>(width));
    for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
            float intensity = 0;
            auto R = pixel_mat[i][j][0];
            auto G = pixel_mat[i][j][1];
            auto B = pixel_mat[i][j][2];
            if (algo_name == "average") {
                intensity = (R + G + B) / 3.0;
            } else if (algo_name == "min-max") {
                intensity = (std::min(R, std::min(G, B)) +
                             std::max(R, std::max(G, B))) /
                            2.0;
            } else if (algo_name == "luminosity") {
                intensity = 0.21 * R + 0.72 * G + 0.07 * B;
            } else {
                throw std::runtime_error("Unrecognized algo name : " + algo_name);
            }

            intensity_mat[i][j] = intensity;
        }
    }

    return intensity_mat;
}

intensityMat normalizeIntensityMatrix(intensityMat intensity_mat)
{
    float max_intensity = 0, min_intensity = MAX_PIXEL_VALUE;
    [&intensity_mat, &min_intensity, &max_intensity]() -> void {
        for (auto const& row : intensity_mat) {
            for (auto const& intensity : row) {
                min_intensity = std::min(min_intensity, intensity);
                max_intensity = std::max(max_intensity, intensity);
            }
        }
    }();

    for (auto& row : intensity_mat) {
        for (auto& intensity : row) {
            intensity = MAX_PIXEL_VALUE * (intensity - min_intensity) / (max_intensity - min_intensity);
        }
    }

    return intensity_mat;
}

intensityMat invertIntensityMat(intensityMat intensity_mat)
{
    for (auto& row : intensity_mat) {
        for (auto& intensity : row) {
            intensity = MAX_PIXEL_VALUE - intensity;
        }
    }

    return intensity_mat;
}

void printAsciiImage(intensityMat const& normalized_mat)
{
    static float const multiplier = (ascii_chars.size() - 1) / MAX_PIXEL_VALUE;

    for (auto const& row : normalized_mat) {
        for (auto const& intensity : row) {
            int index = multiplier * intensity;
            char pixel = ascii_chars[index];
            std::cout << pixel << pixel << pixel;
        }
        std::cout << '\n';
    }
}