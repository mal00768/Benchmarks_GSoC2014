/*
 dense matrix and scalar addition kernel
*/

namespace boost {

double dmatmscalaradd(size_t N, size_t iterations = 1) {
    
    boost::numeric::ublas::matrix<double> a(N, N), b(N, N);
    double c = 3;
    
    minit(b.size1(), b);
    
    std::vector<double> times;
    for(size_t i = 0; i < iterations; ++i){
        
        auto start = std::chrono::steady_clock::now();
        noalias(a) = b + boost::numeric::ublas::scalar_matrix<double>(N, N, c);
        auto end = std::chrono::steady_clock::now();
        
        auto diff = end - start;
        times.push_back(std::chrono::duration<double, std::milli> (diff).count()); //save time in ms for each iteration
    }
    
    double tmin = *(std::min_element(times.begin(), times.end()));
    double tavg = average_time(times);
    /*
     // check to see if nothing happened during rum to invalidate the times
     if(tmin*(1.0 + deviation*0.01) < tavg){
     std::cerr << "uBLAS kernel 'dmatscalaradd': Time deviation too large!!!" << std::endl;
     }
     */
    return tavg;
    
}

}