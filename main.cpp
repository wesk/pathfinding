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
    pangolin::TypedImage img1 = pangolin::LoadImage(filename);
    //pangolin::TypedImage img2 = pangolin::LoadImage(filename);
    //instantiate grid, size to image
    grid myGrid(img1.h,img1.w);
    std::cout<<img1.h<<" "<<img1.w<<std::endl;

    //here we modify it
    // Iterate over image array // example operation
//    for(unsigned int y=0; y<img1.h; ++y) {
//        for(unsigned int x=0; x<img1.w; ++x) {
//            img1.ptr[img1.pitch*y + x] = ((y/10)%2)*((x/10)%2)*255;

//        }
//    }

    // copying the image data into grid class
    for(unsigned int y = 0; y<img1.h; y++){
        for(unsigned int x = 0; x<img1.w; x++){
            if(img1.ptr[img1.pitch*y + x] == 0){
                myGrid.fillSingle(x,y);
            }
        }
    }

    //choose semi-arbitrary start point. Not the best system, can improve
    myGrid.setStart({50,50});
    myGrid.setGoal({(int)img1.h-50,(int)img1.w-50});

    //draw 5x5 squares on the start and end
    for(unsigned int y = 45; y< 55; y++){
        for(unsigned int x = 45; x<55; x++){
            img1.ptr[img1.pitch*y + x] = 0;
        }
    }
    for(unsigned int y = img1.h-55; y<img1.h-45; y++){
        for(unsigned int x = img1.w-55; x<img1.w-45; x++){
            img1.ptr[img1.pitch*y + x] = 0;
        }
    }

    std::cout<<"preparing to solve\n";
    pathfinder solver(myGrid);
    solver.findPath();
    std::cout<<"solved\n";
    myGrid.print();

    //draw the solution on the picture
    for(unsigned int row = 0; row<img1.h; row++){
        for(unsigned int col = 0; col<img1.w; col++){
            if(solver.getSolved().getNodeValue({row,col}) == 2){
                img1.ptr[img1.pitch*col + row] = 0;
            }
        }
    }

    std::cout<<"done modding file\n";

    pangolin::CreateWindowAndBind("Main",2*img1.w,img1.h); //2x width, accomidating 2 views
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    pangolin::DisplayBase().SetLayout(pangolin::LayoutEqual);
    pangolin::View& mapview = pangolin::CreateDisplay()
            .SetAspect( (float)img1.w / img1.h );
    pangolin::View& planview = pangolin::CreateDisplay()
            .SetAspect( (float)img1.w / img1.h ); // to prevent aspect ratio squishing

    // Copy image onto GPU
    pangolin::GlTexture tex(img1.w, img1.h, GL_LUMINANCE, false, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE);
    tex.Upload(img1.ptr, GL_LUMINANCE, GL_UNSIGNED_BYTE);


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
