#include "plotInterface.hpp"

namespace ASALI
{
    plotInterface::plotInterface()
    {
    }

    double plotInterface::maxElement(const std::vector<double> v)
    {
        double max = DBL_MIN;

        for (unsigned int i = 0; i < v.size(); i++)
            max = std::max(v[i], max);

        return max;
    }

    double plotInterface::minElement(const std::vector<double> v)
    {
        double min = DBL_MAX;

        for (unsigned int i = 0; i < v.size(); i++)
            min = std::min(v[i], min);

        return min;
    }

    int plotInterface::maxElement(const std::vector<int> v)
    {
        int max = INT_MIN;

        for (unsigned int i = 0; i < v.size(); i++)
            max = std::max(v[i], max);

        return max;
    }

    int plotInterface::minElement(const std::vector<int> v)
    {
        int min = INT_MAX;

        for (unsigned int i = 0; i < v.size(); i++)
            min = std::min(v[i], min);

        return min;
    }

    void plotInterface::setSize(int nsize)
    {
        nsize_ = nsize;
        x_ = new PLFLT[nsize_];
        y_ = new PLFLT[nsize_];
    }

    void plotInterface::setXlimits(double xmin, double xmax)
    {
        xmin_ = xmin;
        xmax_ = xmax;
    }

    void plotInterface::setYlimits(double ymin, double ymax)
    {
        ymin_ = ymin;
        ymax_ = ymax;
    }

    void plotInterface::setXlabel(std::string xlabel)
    {
        xlabel_ = xlabel;
    }

    void plotInterface::setYlabel(std::string ylabel)
    {
        ylabel_ = ylabel;
    }

    void plotInterface::setTitle(std::string title)
    {
        title_ = title;
    }

    void plotInterface::setData(std::vector<double> x, std::vector<double> y)
    {
        this->setSize(x.size());
        this->setXlimits(this->maxElement(x), this->minElement(x));
        this->setYlimits(this->maxElement(y), this->minElement(y));

        for (unsigned int i = 0; i < nsize_; i++)
        {
            x_[i] = x[i];
            y_[i] = y[i];
        }
    }

    void plotInterface::show()
    {
        pls = new plstream();

        // Parse and process command line arguments
        pls->init();

        // Create a labelled box to hold the plot.
        pls->env(xmin_, xmax_, ymin_, ymax_, 0, 0);
        pls->lab(xlabel_.c_str(), ylabel_.c_str(), title_.c_str());

        // Plot the data that was prepared above.
        pls->line(nsize_, x_, y_);

        delete pls;
    }

    plotInterface::~plotInterface()
    {
    }

}