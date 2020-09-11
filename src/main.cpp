#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdexcept>

#include "image_ops.hpp"

int main(int argc, char** argv) {
    std::string img_loc{};
    std::string intensity_algo_name{ "average" };

    if (argc == 2) {
        img_loc = std::move(argv[1]);
    } else if (argc == 3) {
        img_loc = std::move(argv[1]);
        intensity_algo_name = std::move(argv[2]);
    } else {
        throw std::runtime_error("Expected an image file.");
    }

    // cv::namedWindow("Simple Demo", cv::WINDOW_AUTOSIZE);
    // cv::imshow("Simple Demo", img);
    // cv::waitKey(100);
    // cv::destroyAllWindows();

    auto pixel_mat = getPixelMatrix(img_loc);
    auto intensity_mat = getIntensityMatrix(pixel_mat, intensity_algo_name);
    auto normalized_mat = normalizeIntensityMatrix(intensity_mat);
    // intensityMat inverted_mat = invertIntensityMat(intensity_mat);
    // intensityMat normalized_mat = normalizeIntensityMatrix(inverted_mat);

    printAsciiImage(normalized_mat);
    return 0;
}