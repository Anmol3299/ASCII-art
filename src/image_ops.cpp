#include "image_ops.hpp"

#include <stdexcept>

pixelMat getPixelMatrix(std::string const& img_loc) {
    cv::Mat img = cv::imread(img_loc);
    if (img.empty()) {
        throw std::runtime_error("Not a valid image file.");
    }

    if (double div_factor = img.cols / 400; img.cols > 400) {
        cv::resize(img, img, cv::Size(), 1 / div_factor, 1 / div_factor,
                   cv::INTER_AREA);
    }

    auto height = img.rows;
    auto width = img.cols;
    pixelMat pixel_mat(height, std::vector<std::array<uint16_t, 3>>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto bgr_pixel = img.at<cv::Vec3b>(i, j);
            pixel_mat[i][j][0] = bgr_pixel[2];
            pixel_mat[i][j][1] = bgr_pixel[1];
            pixel_mat[i][j][2] = bgr_pixel[0];
        }
    }

    return pixel_mat;
}

intensityMat getIntensityMatrix(pixelMat const& pixel_mat,
                                std::string const& algo_name) {
    auto height = pixel_mat.size();
    auto width = pixel_mat[0].size();
    intensityMat intensity_mat(height, std::vector<float>(width));
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            float intensity = 0;
            auto [R, G, B] = pixel_mat[i][j];
            if (algo_name == "average") {
                intensity = (R + G + B) / 3.0;
            } else if (algo_name == "min-max") {
                intensity = (std::min(R, std::min(G, B)) +
                             std::max(R, std::max(G, B))) /
                            2.0;
            } else if (algo_name == "luminosity") {
                intensity = 0.21 * R + 0.72 * G + 0.07 * B;
            } else {
                throw std::runtime_error("Unrecognized algo name : " +
                                         algo_name);
            }

            intensity_mat[i][j] = intensity;
        }
    }

    return intensity_mat;
}

intensityMat normalizeIntensityMatrix(intensityMat intensity_mat) noexcept {
    float max_intensity = 0, min_intensity = MAX_PIXEL_VALUE;
    [&] {
        for (auto const& row : intensity_mat) {
            for (auto const& intensity : row) {
                min_intensity = std::min(min_intensity, intensity);
                max_intensity = std::max(max_intensity, intensity);
            }
        }
    }();

    for (auto& row : intensity_mat) {
        for (auto& intensity : row) {
            intensity = MAX_PIXEL_VALUE * (intensity - min_intensity) /
                        (max_intensity - min_intensity);
        }
    }

    return intensity_mat;
}

intensityMat invertIntensityMat(intensityMat intensity_mat) noexcept {
    for (auto& row : intensity_mat) {
        for (auto& intensity : row) {
            intensity = MAX_PIXEL_VALUE - intensity;
        }
    }

    return intensity_mat;
}

void printAsciiImage(intensityMat const& normalized_mat) noexcept {
    constexpr float multiplier = (ascii_chars.size() - 1) / MAX_PIXEL_VALUE;

    for (auto const& row : normalized_mat) {
        for (auto const& intensity : row) {
            size_t index = multiplier * intensity;
            char pixel = ascii_chars[index];
            std::cout << pixel << pixel << pixel;
        }
        std::cout << '\n';
    }
}