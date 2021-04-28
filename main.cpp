#include "plotInterface.hpp"

int main(int argc, char **argv)
{
    int nsize = 100;
    double ymax = 100;

    std::vector<double> x(nsize);
    std::vector<double> y(nsize);

    for (unsigned int i = 0; i < nsize; i++)
    {
        x[i] = (double)(i) / (double)(nsize - 1);
        y[i] = ymax * x[i] * x[i];
    }
    
    ASALI::plotInterface *asaliplot = new ASALI::plotInterface();
    asaliplot->setData(x, y);
    asaliplot->setXlabel("Time [s]");
    asaliplot->setYlabel("Temperature [K]");
    asaliplot->setTitle("Rebu is the best");
    asaliplot->show();

    delete asaliplot;
    return 0;
}