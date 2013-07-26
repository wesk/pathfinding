#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <eigen3/Eigen/Eigen>
#include "grid.h"
#include "node.h"
#include "pathfinder.h"
#include <pangolin/pangolin.h>
#include <pangolin/image_load.h>

int main( int argc, char** argv )
{
    if(argc <= 1) {
        std::cout << "Usage: pangotest filename" << std::endl;
        exit(1);
    }

    // Load image from disk onto CPU
    const std::string filename = argv[1];
    pangolin::TypedImage img = pangolin::LoadImage(filename);

    //here we modify it

    // Iterate over image array // example operation
//    for(int y=0; y<img.h; ++y) {
//        for(int x=0; x<img.w; ++x) {
//            img.ptr[img.pitch*y + x] = ((y/10)%2)*((x/10)%2)*255;

//        }
//    }

    pangolin::CreateWindowAndBind("Main",2*img.w,img.h); //2x width, accomidating 2 views
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    pangolin::DisplayBase().SetLayout(pangolin::LayoutEqual);
    pangolin::View& mapview = pangolin::CreateDisplay()
            .SetAspect( (float)img.w / img.h );
    pangolin::View& planview = pangolin::CreateDisplay()
            .SetAspect( (float)img.w / img.h ); // to prevent aspect ratio squishing

    // Copy image onto GPU
    pangolin::GlTexture tex(img.w, img.h, GL_LUMINANCE, false, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE);
    tex.Upload(img.ptr, GL_LUMINANCE, GL_UNSIGNED_BYTE);


    // Graphics loop
    while( !pangolin::ShouldQuit() )
    {
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mapview.Activate();
        tex.RenderToViewportFlipY();

        planview.Activate();
        tex.RenderToViewportFlipY();

        // Process pangolin events.
        pangolin::FinishFrame();
    }

    return 0;
}
