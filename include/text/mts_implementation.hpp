#ifndef MTS_IMPLEMENTATION_HPP
#define MTS_IMPLEMENTATION_HPP

// pango/cairo includes
#include <glib.h>
#include <pango/pangocairo.h>

// opencv includes
#include <opencv2/core/cvstd.hpp> // cv::String
#include <opencv2/core/mat.hpp> // cv::Mat

// our method includes
#include "text/map_text_synthesizer.hpp"
#include "text/mts_utilities.hpp"
#include "text/mts_basehelper.hpp"
#include "text/mts_texthelper.hpp"
#include "text/mts_bghelper.hpp"

using namespace std;
using boost::random::mt19937;
using boost::random::gamma_distribution;
using boost::random::variate_generator;

namespace cv{
    namespace text{

        class MTSImplementation: public MapTextSynthesizer{

            protected:
                /* Returns the corresponding value given key in config.txt
                 *
                 * key - key in hashmap constructed from config.txt
                 */
                double getParam(string key);

                /* Converts cairo surface to mat object in opencv
                 *
                 * surface - the cairo surface to be converted
                 * mat - the output map object containing the RGB channel
                 *      of surface. alpha channel is thrown away.
                 *
                 * Original code for this method is from Andrey Smorodov
                 * url: https://stackoverflow.com/questions/19948319/how-to-convert-cairo-image-surface-to-opencv-mat-in-c
                 */
                static void cairoToMat(cairo_surface_t *surface,Mat &mat);

                /* Adds Gaussian noise to out
                 *
                 * out - the input and output image
                 */
                void addGaussianNoise(Mat& out);

                /* Adds Gaussian blur to out
                 *
                 * out - the input and output image
                 */
                void addGaussianBlur(Mat& out);

                /* Updates the list of available system fonts by 
                 * clearing and reloading fntList
                 *
                 * fntList - the output
                 * Base of this method from Ben K. Bullock at
                 * url: https://www.lemoda.net/pango/list-fonts/index.html
                 */
                void updateFontNameList(std::vector<String>& fntList);

                /* The list of blocky font names set by user. */
                std::vector<String> blockyFonts_;

                /* The list of regular font names set by user. */
                std::vector<String> regularFonts_;

                /* The list of cursive font names set by user. */
                std::vector<String> cursiveFonts_;

                /* The list of available system font names. */
                std::vector<String> availableFonts_;

                /* Pointers pointing to blocky, regular, cursive font lists. */
                std::shared_ptr<std::vector<String> > fonts_[3];

                /* The list of captions to sample from.*/
                std::vector<String> sampleCaptions_;

                MTS_Utilities utils;

                shared_ptr<MTS_BaseHelper> helper;
                MTS_TextHelper th;
                MTS_BackgroundHelper bh;

                /* Generator for sigma used in Gaussian noise method. */
                gamma_distribution<> noise_dist;
                variate_generator<mt19937, gamma_distribution<> > noise_gen;

            public:

                /* Constructor */
                MTSImplementation();

                /* See MapTextSynthesizer for documentations.*/

                void setBlockyFonts(std::vector<String>& fntList);

                void setRegularFonts(std::vector<String>& fntList);

                void setCursiveFonts(std::vector<String>& fntList);

                void setSampleCaptions (std::vector<String>& words);

                void generateSample(CV_OUT String &caption, CV_OUT Mat & sample);
        };

    }  //namespace text
}  //namespace cv

#endif
