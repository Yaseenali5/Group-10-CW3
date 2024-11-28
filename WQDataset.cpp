#include "WQDataset.hpp"
#include <stdexcept>
#include <numeric>
#include <fstream>
#include <sstream>
#include "csv.hpp" 

void WQDataset::loadData(const std::string& filename) {
    csv::CSVReader reader(filename);
    data.clear();

    for (const auto& row : reader) {
        WQSample sample(
            row["@id"].get<>(),
            row["sample.samplingPoint"].get<>(),
            row["sample.samplingPoint.notation"].get<>(),
            row["sample.samplingPoint.label"].get<>(),
            row["sample.sampleDateTime"].get<>(),
            row["determinand.label"].get<>(),
            row["determinand.definition"].get<>(),
            row["determinand.notation"].get<>(),
            row["resultQualifier.notation"].get<>(),
            row["result"].get<double>(),
            row["codedResultInterpretation.interpretation"].get<>(),
            row["determinand.unit.label"].get<>(),
            row["sample.sampledMaterialType.label"].get<>(),
            row["sample.isComplianceSample"].get<bool>(),
            row["sample.purpose.label"].get<>(),
            row["sample.samplingPoint.easting"].get<double>(),
            row["sample.samplingPoint.northing"].get<double>()
        );

        data.push_back(sample);
    }
}

void WQDataset::clear() {
    data.clear();
}

void WQDataset::checkDataExists() const {
    if (data.empty()) {
        throw std::runtime_error("Dataset is empty!");
    }
}