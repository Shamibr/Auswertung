#include "vent.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void VentilationCurve::addDataPoint(double t, double v) {
    time.push_back(t);
    values.push_back(v);
}

VentilationCurve VentilationCurve::readCSV(const std::string& filename) {
    VentilationCurve curve;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::string line;
    std::getline(file, line);  // Erste Zeile (Header) überspringen

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string time_str, value_str;

        std::getline(ss, time_str, ',');
        std::getline(ss, value_str, ',');

        double time = std::stod(time_str);
        double value = std::stod(value_str);

        curve.addDataPoint(time, value);
    }

    file.close();
    return curve;
}

std::vector<double> VentilationCurve::smoothCurve(int window_size) const {
    std::vector<double> smoothed_values;
    int half_window = window_size / 2;
    for (size_t i = 0; i < values.size(); ++i) {
        double sum = 0.0;
        int count = 0;
        for (int j = -half_window; j <= half_window; ++j) {
            if ((i + j) >= 0 && (i + j) < values.size()) {
                sum += values[i + j];
                count++;
            }
        }
        smoothed_values.push_back(sum / count);
    }
    return smoothed_values;
}
