#ifndef PLOTINTERFACE_H
#define PLOTINTERFACE_H
#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <ctime>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <limits>
#include <climits>
#include <numeric>
#include <functional>
#include <float.h>

#include "plplot.h"
#include "plstream.h"

namespace ASALI
{
    class plotInterface
    {
    public:
        plotInterface();

        void setData(std::vector<double> x, std::vector<double> y, std::string label);
        void setXlimits(double xmin, double xmax);
        void setYlimits(double ymin, double ymax);
        void setXlabel(std::string xlabel);
        void setYlabel(std::string ylabel);
        void setTitle(std::string title);
        void setTextColor(int r, int b, int g);
        void setBackgroundColor(int r, int b, int g);
        void setLegendPosition(const std::string position);
        void setOutputFormat(const std::string outputFormat);
        void setOutputFileName(const std::string fileName);
        void legend();
        void show();

        virtual ~plotInterface();

    private:
        void convertToPLFLT(std::vector<double> v, PLFLT *p);
        void convertToPLINT(std::vector<int> v, PLINT *p);

        double minElement(const std::vector<double> v);
        double maxElement(const std::vector<double> v);

        int minElement(const std::vector<int> v);
        int maxElement(const std::vector<int> v);

        plstream *pls;

        int nSize_;
        int nLegend_;

        std::string xLabel_;
        std::string yLabel_;
        std::string title_;
        std::string outputFormat_;
        std::string fileName_;

        bool isLegend_;
        bool isOnFile_;

        PLINT legendPosition_;
        PLINT optBase_;
        PLINT nCol_;
        PLINT nRow_;

        PLFLT xmax_;
        PLFLT xmin_;
        PLFLT ymax_;
        PLFLT ymin_;
        PLFLT legendWidth_;
        PLFLT legendHeight_;

        std::vector<std::string> legendText_;
        std::vector<std::string> onScreenOutputFormats_;

        std::vector<int> textColors_;
        std::vector<int> lineColors_;
        std::vector<int> lineStyles_;
        std::vector<int> optArray_;
        std::vector<int> textColor_;
        std::vector<int> bgColor_;

        std::vector<double> lineWidths_;

        std::vector<std::vector<double>> x_;
        std::vector<std::vector<double>> y_;
    };
}
#endif