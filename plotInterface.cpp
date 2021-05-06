#include "plotInterface.hpp"

namespace ASALI
{
    plotInterface::plotInterface() : xLabel_(""),
                                    yLabel_(""),
                                    title_(""),
                                    outputFormat_("?"),
    isLegend_(false),
    isOnFile_(true),
                                     legendPosition_(PL_POSITION_TOP | PL_POSITION_OUTSIDE),
                                     optBase_(PL_LEGEND_BACKGROUND | PL_LEGEND_BOUNDING_BOX),
                                     nCol_(0),
                                     nRow_(0),
                                     xmax_(DBL_MIN),
                                     xmin_(DBL_MAX),
                                     ymax_(DBL_MIN),
                                     ymin_(DBL_MAX),
                                     onScreenOutputFormats_({"xcairo", "wxwidgets", "qtwidget"}),
                                     textColor_({255, 255, 235}),
                                     bgColor_({0, 0, 0})

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

    void plotInterface::setXlimits(double xmax, double xmin)
    {
        xmin_ = std::min(xmin, xmin_);
        xmax_ = std::max(xmax, xmax_);
    }

    void plotInterface::setYlimits(double ymax, double ymin)
    {
        ymin_ = std::min(ymin, ymin_);
        ymax_ = std::max(ymax, ymax_);
    }

    void plotInterface::setXlabel(std::string xlabel)
    {
        xLabel_ = xlabel;
    }

    void plotInterface::setYlabel(std::string ylabel)
    {
        yLabel_ = ylabel;
    }

    void plotInterface::setTitle(std::string title)
    {
        title_ = title;
    }

    void plotInterface::setTextColor(int r, int b, int g)
    {
        textColor_[0] = r;
        textColor_[1] = b;
        textColor_[2] = g;
    }

    void plotInterface::setBackgroundColor(int r, int b, int g)
    {
        bgColor_[0] = r;
        bgColor_[1] = b;
        bgColor_[2] = g;
    }

    void plotInterface::setData(std::vector<double> x, std::vector<double> y, std::string label)
    {
        x_.push_back(x);
        y_.push_back(y);

        legendText_.push_back(label);

        nLegend_ = x_.size();

        this->setXlimits(this->maxElement(x), this->minElement(x));
        this->setYlimits(this->maxElement(y), this->minElement(y));
    }

    void plotInterface::setLegendPosition(const std::string position)
    {
        if (position == "top")
        {
            legendPosition_ = PL_POSITION_OUTSIDE | PL_POSITION_TOP;
            nCol_ = nLegend_;
        }
        else if ( position == "bottom")
        {
            legendPosition_ = PL_POSITION_OUTSIDE | PL_POSITION_BOTTOM;
            nCol_ = nLegend_;
        }
        else if ( position == "left")
        {
            legendPosition_ = PL_POSITION_INSIDE | PL_POSITION_LEFT;
            nRow_ = nLegend_;
        }
        else if ( position == "right")
        {
            legendPosition_ = PL_POSITION_INSIDE | PL_POSITION_RIGHT;
            nRow_ = nLegend_;
        }
        else if ( position == "left_top")
        {
            legendPosition_ = PL_POSITION_INSIDE | PL_POSITION_LEFT | PL_POSITION_TOP;
            nRow_ = nLegend_;
        }
        else if ( position == "right_top")
        {
            legendPosition_ = PL_POSITION_INSIDE | PL_POSITION_RIGHT | PL_POSITION_TOP;
            nRow_ = nLegend_;
        }        
        else if ( position == "left_bottom")
        {
            legendPosition_ = PL_POSITION_INSIDE | PL_POSITION_LEFT | PL_POSITION_BOTTOM;
            nRow_ = nLegend_;
        }
        else if ( position == "right_bottom")
        {
            legendPosition_ = PL_POSITION_INSIDE | PL_POSITION_RIGHT | PL_POSITION_BOTTOM;
            nRow_ = nLegend_;
        }
        else
        {
            nCol_ = nLegend_;
        }
    }

    void plotInterface::setOutputFormat(std::string outputFormat)
    {
        outputFormat_ = outputFormat;
        for (unsigned int i=0;i<onScreenOutputFormats_.size();i++)
        {
            if ( outputFormat_ == onScreenOutputFormats_[i])
            {
                isOnFile_ = false;
                break;
            }
        }
    }


    void plotInterface::setOutputFileName(std::string fileName)
    {
        fileName_ = fileName;
    }


    void plotInterface::legend()
    {
        isLegend_ = true;

        textColors_.resize(nLegend_);

        lineColors_.resize(nLegend_);
        lineStyles_.resize(nLegend_);
        lineWidths_.resize(nLegend_);

        optArray_.resize(nLegend_);

        for (unsigned int i = 0; i < nLegend_; i++)
        {
            textColors_[i] = 1;
            lineColors_[i] = i + 2;
            lineStyles_[i] = 1;
            lineWidths_[i] = 1.0;
            optArray_[i] = PL_LEGEND_LINE;
        }
    }

    void plotInterface::convertToPLFLT(std::vector<double> v, PLFLT *p)
    {
        for (unsigned int i = 0; i < v.size(); i++)
        {
            p[i] = v[i];
        }
    }

    void plotInterface::convertToPLINT(std::vector<int> v, PLINT *p)
    {
        for (unsigned int i = 0; i < v.size(); i++)
        {
            p[i] = v[i];
        }
    }

    void plotInterface::show()
    {
        pls = new plstream();

        // Change Background Color
        pls->scolbg(bgColor_[0], bgColor_[1], bgColor_[2]);

        // Set Text Color
        pls->scol0(1, textColor_[0], textColor_[1], textColor_[2]);

        // Create output format
        pls->sdev(outputFormat_.c_str());
        if (!fileName_.empty() && isOnFile_)
        {
            pls->sfnam(fileName_.c_str());
        }

        // Parse and process command line arguments
        pls->init();

        // Create a labelled box to hold the plot.
        pls->env(xmin_, xmax_, ymin_, ymax_, 0, 0);
        pls->lab(xLabel_.c_str(), yLabel_.c_str(), title_.c_str());

        // Plot the data that was prepared above.
        for (unsigned int i = 0; i < nLegend_; i++)
        {
            PLFLT x[x_[i].size()];
            this->convertToPLFLT(x_[i], x);
            PLFLT y[y_[i].size()];
            this->convertToPLFLT(y_[i], y);

            pls->col0(i + 2);
            pls->line(x_[i].size(), x, y);
        }

        if (isLegend_ == true)
        {
            PLINT opt_array[nLegend_];
            this->convertToPLINT(optArray_, opt_array);

            std::vector<const char*> texts(nLegend_);
            for (unsigned int i = 0; i < nLegend_; i++)
            {
                texts[i] = legendText_[i].c_str();
            }
            PLINT text_colors[nLegend_];
            this->convertToPLINT(textColors_, text_colors);

            PLINT line_colors[nLegend_];
            this->convertToPLINT(lineColors_, line_colors);
            PLINT line_styles[nLegend_];
            this->convertToPLINT(lineStyles_, line_styles);
            PLFLT line_widths[nLegend_];
            this->convertToPLFLT(lineWidths_, line_widths);

            pls->legend(&legendWidth_,              //p_legend_width
                        &legendHeight_,             //p_legend_height
                        optBase_,                  //opt
                        legendPosition_,           //position
                        0.05,                       //x
                        0.05,                       //y
                        0.1,                        //plot_width
                        0,                          //bg_color
                        0,                          //bb_color
                        1,                          //bb_style
                        nRow_,                      //nrow
                        nCol_,                      //ncolumn
                        nLegend_,                   //nlegend
                        opt_array,                  //opt_array
                        1.0,                        //text_offset
                        1.0,                        //text_scale
                        2.0,                        //text_spacing
                        1.,                         //test_justification
                        text_colors,                //text_colors
                        texts.data(),               //texts
                        NULL,                       //box_colors
                        NULL,                       //box_patterns
                        NULL,                       //box_scales
                        NULL,                       //box_line_widths
                        line_colors,                //line_colors
                        line_styles,                //line_styles
                        line_widths,                //line_widths
                        NULL,                       //symbol_colors
                        NULL,                       //symbol_scales
                        NULL,                       //symbol_numbers
                        NULL);                      //symbols
        }

        delete pls;
    }

    plotInterface::~plotInterface()
    {
    }

}