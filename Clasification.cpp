#include "Clasification.hpp"





void Clasification::cargarImages(){

    std::vector<std::string> planes; 
    std::vector<std::string> books; 
    std::vector<std::string> balls; 
    std::string path1 = "/home/alex/Documents/8vo/vision-artificial/practicas/parte-2/Data/airplane";
    cv::glob(path1, planes, false);

    std::string path2 = "/home/alex/Documents/8vo/vision-artificial/practicas/parte-2/Data/ball";
    cv::glob(path2, balls, false);

    std::string path3 = "/home/alex/Documents/8vo/vision-artificial/practicas/parte-2/Data/books";
    cv::glob(path3, books, false);

    /*std::cout << fileName.size() << std::endl;*/
    /*for(int i =0; i < balls.size(); i++){
        std::cout << balls[i] << std::endl;
    }*/

    test_train(planes, balls, books);
 
}

void Clasification::prueba(){
    cargarImages();

    //CommandLineParser parser( argc, argv, "{@input | lena.jpg | input image}" );
    Mat src = imread( samples::findFile( test_planes[10] ), IMREAD_COLOR );

    Mat hist = histograma(src,0);
    
    for (int j=0;j<hist.rows;j++){

        cout <<hist.at<float>(j)<< "\n";
    }

}



Mat Clasification::histograma(Mat src, int canal){

    
if( src.empty() )
    {
        cout<<"VACIO..."<<"/n";
    }
    vector<Mat> bgr_planes;
    split( src, bgr_planes );
    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange = { range };
    bool uniform = true, accumulate = false;
    Mat b_hist, g_hist, r_hist;
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    normalize(b_hist, b_hist, 0, 1024, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, 1024, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, 1024, NORM_MINMAX, -1, Mat() );

    if (canal==0)
    {
        
        return b_hist;
    }
    if (canal==1)
    {
        return g_hist;
    }
    if (canal==2)
    {
        return r_hist;
    }

  return src;
        
}


void Clasification::test_train(vector<string> planes, vector<string>balls, vector<string>books){

    for(int i =0; i < round((planes.size())*0.8); i++){
       train_planes.push_back(planes[i]);
       // std::cout << train_planes[i] << std::endl;
    }

    for(int i =0; i < round((balls.size())*0.8); i++){
       train_balls.push_back(balls[i]);
       // std::cout << train_balls[i] << std::endl;
    }

   for(int i =0; i < round((books.size())*0.8); i++){
       train_books.push_back(books[i]);
        //std::cout << train_books[i] << std::endl;
    }




    for(int i = round((books.size())*0.8); i < books.size(); i++){
       test_books.push_back(books[i]);
       
    }
    //std::cout << test_books.size() << std::endl;

    for(int i = round((balls.size())*0.8); i < balls.size(); i++){
       test_balls.push_back(balls[i]);
       
    }
    //std::cout << test_balls.size() << std::endl;

    for(int i = round((planes.size())*0.8); i < planes.size(); i++){
       test_planes.push_back(planes[i]);
       
    }
    //std::cout << test_planes.size() << std::endl;

  


}


void Clasification::clasificar(){
    double maxPlanes;
    double maxBooks;
    double maxBalls;

    int aciertosBooks=0;
    int aciertosBalls=0;
    int aciertosPlanes=0;

    int fallasPlanes =0;
    int fallasBooks=0;
    int fallasBalls=0;

    int bandera =0;
    cargarImages();


    for (int j=0;j<test_planes.size();j++){
         Mat imagen = imread( samples::findFile( test_planes[j] ), IMREAD_COLOR );
       // Mat imagen = imread(test_planes[j], IMREAD_UNCHANGED);
      
            maxPlanes = distancia(imagen, train_planes);
         //   cout << "LLEGO 1 EMPIEZA 2.."<< maxPlanes <<"\n";
            maxBalls = distancia(imagen, train_balls);
         //   cout << "LLEGO 2 EMPIEZA 3.."<<maxBalls <<"\n";
            
            maxBooks = distancia(imagen, train_books);
         //   cout << "LLEGO 3 FINALIZA.."<<maxBooks << "\n";
            if(maxPlanes > maxBalls && maxPlanes >maxBooks ) {
                aciertosPlanes+=1;
            }else{
                fallasPlanes+=1;
            }   
    }


    for (int j=0;j<test_books.size();j++){
        Mat imagen = imread(test_books[j], IMREAD_UNCHANGED);
            maxPlanes = distancia(imagen, train_planes);
            maxBalls = distancia(imagen, train_balls);
            maxBooks = distancia(imagen, train_books);
            if(maxBooks > maxBalls && maxBooks >maxPlanes ) {
                aciertosBooks+=1;
            }else{
                fallasBooks+=1;
            }   
    }

    for (int j=0;j<test_balls.size();j++){
        Mat imagen = imread(test_balls[j], IMREAD_UNCHANGED);
            maxPlanes = distancia(imagen, train_planes);
            maxBalls = distancia(imagen, train_balls);
            maxBooks = distancia(imagen, train_books);
            if(maxBalls > maxBooks && maxBalls > maxPlanes ) {
                aciertosBalls+=1;
            }else{
                fallasBalls+=1;
            }   
    }


    double p1=("%f" ,(double)aciertosBooks/test_books.size());
    double p2=("%f" ,(double)aciertosBooks/test_books.size());
    double p3=("%f" ,(double)aciertosBalls/test_balls.size());
    

    cout << "Categoria Planes" << " = " << p1 << " % "<< " Aciertos = " << aciertosPlanes <<" Fallas = "<<fallasPlanes<<  " Total test = "<< test_planes.size()<< "\n";
    cout << "Categoria Books" << " = " << p2 << " % "<< " Aciertos = " << aciertosBooks <<" Fallas = "<<fallasBooks<<  " Total test = "<< test_books.size()<< "\n";
    cout << "Categoria Balls" << " = " << p3 << " % " << " Aciertos = " << aciertosBalls <<" Fallas = "<<fallasBalls<<  " Total test = "<< test_balls.size()<< "\n";

}
    

double Clasification::distancia(Mat imageTest, vector<string> train){

    vector<double> calculos;
    Mat imagen;

    Mat ib0,ig0,ir0;
    Mat ib1, ig1, ir1;
    double cb, cg, cr;


    ib0 = histograma(imageTest,0);
    ig0 = histograma(imageTest,1);
    ir0 = histograma(imageTest,2);

    
    int jj=0;

    for (int j=0;j<train.size();j++){
        
        imagen = imread(train[j], IMREAD_UNCHANGED);
        jj+=1;
       // cout << train[j] << "\n";

        

        ib1 = histograma(imagen,0);
        ig1 = histograma(imagen,1);
        ir1 = histograma(imagen,2);


        //cout << "ib1.."<<ib1 << "\n";
        //cout << "ib0.."<<ib0 << "\n";
        //cout << "............................." << "\n";
        //cout << "ig1.."<<ig1 << "\n";
        //cout << "ir1.."<<ir1 << "\n";

        cb = euclideanDistance(ib0, ib1);
        cg = euclideanDistance(ig0, ig1);
        cr = euclideanDistance(ir0, ir1);

        //cout << "cb.."<<cb << "\n";
        //cout << "cg.."<<cg << "\n";
        //cout << "cr.."<<cr << "\n";
        //cout << "cont.."<<jj << "\n";

        calculos.push_back(cb+cg+cr);
        //cout << "TRAIN.."<<train_planes.size() << "\n";

    }
    int maxElementIndex = std::max_element(calculos.begin(),calculos.end()) - calculos.begin();
    double maxElement = *std::max_element(calculos.begin(), calculos.end());

   // cout << "Valor retornado.."<<maxElement << "\n";
   
    return maxElement;
    

}


double Clasification::euclideanDistance(Mat histTest, Mat histTrain){
    double d = 0.0;
  
    double pixelTest =0;
    double pixelTrain =0;
    for (int j=0;j<histTest.rows;j++){
        
        pixelTest = histTest.at<float>(j);
        //cout << "pixelTest.."<<pixelTest << "\n";
        pixelTrain = histTrain.at<float>(j);
        //cout << "pixelTrain.."<<pixelTrain << "\n";
        d+=(pow((pixelTest-pixelTrain),2));
        //cout << "Distancia Euclidea.."<<d << "\n";
        //cout << "........................"<<"\n";
    }

    d = sqrt(d);
    //cout << "Distance: " << " i: " << i << " :: " << d << endl;

    return d;
}








