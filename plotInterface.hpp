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

        int nsize_;
        int nlegend_;

        std::string xlabel_;
        std::string ylabel_;
        std::string title_;

        bool is_legend_;

        PLINT legend_position_;
        PLINT opt_base_;
        PLINT ncol_;
        PLINT nrow_;

        PLFLT xmax_;
        PLFLT xmin_;
        PLFLT ymax_;
        PLFLT ymin_;
        PLFLT legend_width;
        PLFLT legend_height;

        std::vector<std::string> legend_text_;

        std::vector<int> text_colors_;
        std::vector<int> line_colors_;
        std::vector<int> line_styles_;
        std::vector<int> opt_array_;
        std::vector<int> text_color_;
        std::vector<int> bg_color_;

        std::vector<double> line_widths_;

        std::vector<std::vector<double>> x_;
        std::vector<std::vector<double>> y_;
    };
}
#endif