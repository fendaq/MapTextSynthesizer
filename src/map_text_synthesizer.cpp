#include "precomp.hpp"

#include "opencv2/text/map_text_synthesizer.hpp"
#include "opencv2/text/mts_implementation.hpp"

using namespace std;

namespace cv{
    namespace text{

        MapTextSynthesizer::MapTextSynthesizer(){}

        Ptr<MapTextSynthesizer> MapTextSynthesizer::create(){
            Ptr<MapTextSynthesizer> mts(new MTSImplementation());
            return mts;
        }

    }  //namespace text
}  //namespace cv
