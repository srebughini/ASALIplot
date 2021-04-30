#include "plotInterface.hpp"

namespace ASALI
{
    plotInterface::plotInterface() : is_legend_(false),
                                     legend_position_(PL_POSITION_TOP | PL_POSITION_OUTSIDE),
                                     opt_base_(PL_LEGEND_BACKGROUND | PL_LEGEND_BOUNDING_BOX),
                                     xmax_(DBL_MIN),
                                     xmin_(DBL_MAX),
                                     ymax_(DBL_MIN),
                                     ymin_(DBL_MAX),
                                     text_color_({255,255,235}),
                                     bg_color_({0,0,0})

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

    void plotInterface::setXlimits(double xmin, double xmax)
    {
        xmin_ = std::min(xmin, xmin_);
        xmax_ = std::max(xmax, xmax_);
    }

    void plotInterface::setYlimits(double ymin, double ymax)
    {
        ymin_ = std::min(ymin, ymin_);
        ymax_ = std::max(ymax, ymax_);
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

    void plotInterface::setTextColor(int r, int b, int g)
    {
        text_color_[0] = r;
        text_color_[1] = b;
        text_color_[2] = g;
    }

    void plotInterface::setBackgroundColor(int r, int b, int g)
    {
        bg_color_[0] = r;
        bg_color_[1] = b;
        bg_color_[2] = g;
    }

    void plotInterface::setData(std::vector<double> x, std::vector<double> y, std::string label)
    {
        x_.push_back(x);
        y_.push_back(y);
        legend_text_.push_back(label);

        nlegend_ = x_.size();

        this->setXlimits(this->maxElement(x), this->minElement(x));
        this->setYlimits(this->maxElement(y), this->minElement(y));
    }

    void plotInterface::setLegendPosition(const std::string inside_outside,
                                          const std::string left_right_center,
                                          const std::string top_bottom_center)
    {
        PLINT pl_top_bottom_center = PL_POSITION_TOP;
        if (top_bottom_center == "bottom")
        {
            pl_top_bottom_center = PL_POSITION_BOTTOM;
        }

        PLINT pl_inside_outside = PL_POSITION_INSIDE;
        if (inside_outside == "outside")
        {
            pl_inside_outside = PL_POSITION_OUTSIDE;
        }

        if (left_right_center == "left")
        {
            if (top_bottom_center == "center")
            {
                legend_position_ = PL_POSITION_LEFT | pl_inside_outside;
            }
            else
            {
                legend_position_ = PL_POSITION_LEFT | pl_top_bottom_center | pl_inside_outside;
            }
        }
        else if (left_right_center == "right")
        {
            if (top_bottom_center == "center")
            {
                legend_position_ = PL_POSITION_RIGHT | pl_inside_outside;
            }
            else
            {
                legend_position_ = PL_POSITION_RIGHT | pl_top_bottom_center | pl_inside_outside;
            }
        }
        else
        {
            legend_position_ = pl_top_bottom_center | pl_inside_outside;
        }
    }

    void plotInterface::legend()
    {
        is_legend_ = true;

        text_colors_.resize(nlegend_);

        line_colors_.resize(nlegend_);
        line_styles_.resize(nlegend_);
        line_widths_.resize(nlegend_);

        legend_symbols_.resize(nlegend_);
        symbol_colors_.resize(nlegend_);
        symbol_numbers_.resize(nlegend_);
        symbol_scales_.resize(nlegend_);

        opt_array_.resize(nlegend_);

        for (unsigned int i = 0; i < nlegend_; i++)
        {
            text_colors_[i] = 1 + (i % 8);
            line_colors_[i] = 1 + (i % 8);
            symbol_colors_[i] = 1 + (i % 8);
            line_styles_[i] = 1;
            line_widths_[i] = 1.0;
            symbol_scales_[i] = 1.;
            symbol_numbers_[i] = 4;
            legend_symbols_[i] = "#(728)";
            opt_array_[i] = PL_LEGEND_LINE | PL_LEGEND_SYMBOL;
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

    void plotInterface::convertToChar(std::vector<std::string> v, char **p)
    {
        for (unsigned int i = 0; i < v.size(); i++)
        {
            p[i] = const_cast<char *>(v[i].c_str());
        }
    }

    void plotInterface::show()
    {
        pls = new plstream();

        // Change Background Color
        pls->scolbg(bg_color_[0], bg_color_[1], bg_color_[2]);

        // Set Text Color
        pls->scol0(1, text_color_[0], text_color_[1], text_color_[2]);

        // Parse and process command line arguments
        pls->init();

        // Create a labelled box to hold the plot.
        pls->env(xmin_, xmax_, ymin_, ymax_, 0, 0);
        pls->lab(xlabel_.c_str(), ylabel_.c_str(), title_.c_str());

        // Plot the data that was prepared above.
        for (unsigned int i = 0; i < nlegend_; i++)
        {
            PLFLT x[x_[i].size()];
            this->convertToPLFLT(x_[i], x);
            PLFLT y[y_[i].size()];
            this->convertToPLFLT(y_[i], y);

            pls->col0(i + 2);
            pls->line(x_[i].size(), x, y);
        }

        if (is_legend_ == true)
        {
            PLINT opt_array[nlegend_];
            this->convertToPLINT(opt_array_, opt_array);

            char *texts[nlegend_];
            this->convertToChar(legend_text_, texts);
            PLINT text_colors[nlegend_];
            this->convertToPLINT(opt_array_, opt_array);

            PLINT line_colors[nlegend_];
            this->convertToPLINT(line_colors_, line_colors);
            PLINT line_styles[nlegend_];
            this->convertToPLINT(line_styles_, line_styles);
            PLFLT line_widths[nlegend_];
            this->convertToPLFLT(line_widths_, line_widths);

            char *symbols[nlegend_];
            this->convertToChar(legend_symbols_, symbols);
            PLINT symbol_colors[nlegend_];
            this->convertToPLINT(symbol_colors_, symbol_colors);
            PLINT symbol_numbers[nlegend_];
            this->convertToPLINT(symbol_numbers_, symbol_numbers);
            PLFLT symbol_scales[nlegend_];
            this->convertToPLFLT(symbol_scales_, symbol_scales);

            pls->legend(&legend_width, &legend_height, opt_base_, legend_position_, 0.05, 0.05,
                        0.1, 15, 1, 1, 0, 0,
                        nlegend_, opt_array, 1.0, 1.0, 2.0,
                        1., text_colors, (const char **)texts,
                        NULL, NULL, NULL, NULL,
                        line_colors, line_styles, line_widths,
                        symbol_colors, symbol_scales, symbol_numbers, (const char **)symbols);
        }

        //char *text[nlegend_];
        //char *sym[nlegend_];

        // Plot legend
        /*
        if (is_legend_ == true)
        {
            pls->legend(&legend_width, &legend_height, opt_base_, legend_position_, 0.05, 0.05,
                        0.1, 15, 1, 1, 0, 0,
                        nlegend_, opt_array_, 1.0, 1.0, 2.0,
                        1., text_colors_, (const char **)text,
                        NULL, NULL, NULL, NULL,
                        line_colors_, line_styles_, line_widths_,
                        symbol_colors_, symbol_scales_, symbol_numbers_, (const char **)sym);
        }*/

        delete pls;
    }

    plotInterface::~plotInterface()
    {
    }

}