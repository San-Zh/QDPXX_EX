/**
 * @file io_prop.cc
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// #include "qdp.h"
#include "chroma.h"

using namespace std;
// using namespace QDP;
using namespace Chroma;

int main(int argc, char const *argv[])
{

    QDP::QDP_initialize(&argc, &argv);

    const int    latdims[Nd] = {8, 8, 8, 8};
    multi1d<int> nrow(4);
    nrow = latdims;
    Layout::setLattSize(nrow);
    Layout::create();


    LatticeFermion ferm01;
    gaussian(ferm01);
    ferm01.print_info("ferm01");

    LatticePropagator prop01;
    gaussian(prop01);
    prop01.print_info("prop01");

    int c, s;
    c = 1;
    s = 2;
    PropToFerm(prop01, ferm01, c, s);

    multi1d<int> site(4);
    site(1);
    int index = Layout::linearSiteIndex(site);

    // XMLFileWriter  xml_out("foo");
    // XMLArrayWriter xml_array(xml_out);
    // write(xml_array, "bar", prop01.elem(index).elem(0, 0).elem(0, 0));

    QDPIO::cout << ferm01.elem(index).elem(0).elem(0) << std::endl;
    QDPIO::cout << prop01.elem(index).elem(0, s).elem(0, c) << std::endl;

    return 0;
}