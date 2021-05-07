#include "plotInterface.hpp"

int main(int argc, char **argv)
{
    int nsize = 100;
    double ymax = 100;

    std::vector<double> x(nsize);
    std::vector<double> y1(nsize);
    std::vector<double> y2(nsize);
    std::vector<double> y3(nsize);

    for (unsigned int i = 0; i < nsize; i++)
    {
        x[i] = (double)(i) / (double)(nsize - 1);
        y1[i] = ymax * x[i] * x[i];
        y2[i] = 2. * ymax * x[i] * x[i];
        y3[i] = 0.25 * ymax * x[i] * x[i];
    }
    
    ASALI::plotInterface *asaliplot = new ASALI::plotInterface();
    for (unsigned int i=0;i<3;i++)
    {
        asaliplot->newFigure();
        asaliplot->setData(x, y1, "rebu1");
        asaliplot->setData(x, y2, "rebu2");
        asaliplot->setData(x, y3, "rebu3");
        asaliplot->setXlabel("Time [s]");
        asaliplot->setYlabel("Temperature [K]");
        asaliplot->setTitle("Rebu is the best");
        asaliplot->setLegendPosition("left");
        asaliplot->setOutputFormat("qtwidget");
        asaliplot->legend();
    }
    //asaliplot->setOutputFileName("rebu.png");

    asaliplot->show();

    delete asaliplot;

    return 0;
}