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

        void setData(std::vector<double> x, std::vector<double> y);
        void setXlimits(double xmin, double xmax);
        void setYlimits(double ymin, double ymax);
        void setXlabel(std::string xlabel);
        void setYlabel(std::string ylabel);
        void setTitle(std::string title);
        void show();

        virtual ~plotInterface();

    private:
        void setSize(int nsize);

        double minElement(const std::vector<double> v);
        double maxElement(const std::vector<double> v);

        int minElement(const std::vector<int> v);
        int maxElement(const std::vector<int> v);

        plstream *pls;

        int nsize_;

        std::string xlabel_;
        std::string ylabel_;
        std::string title_;

        PLFLT xmax_;
        PLFLT xmin_;
        PLFLT ymax_;
        PLFLT ymin_;

        PLFLT *x_;
        PLFLT *y_;
    };
}
#endif