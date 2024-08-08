#ifndef VENT_H
#define VENT_H
#include <vector>
#include <string>

class VentilationCurve {
public:
    std::vector<double> time;  // Zeitstempel
    std::vector<double> values;  // Messwerte

    void addDataPoint(double t, double v);
    static VentilationCurve readCSV(const std::string& filename);
    std::vector<double> smoothCurve(int window_size) const;
};
#endif // VENT_H
