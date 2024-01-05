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
using namespace QDP;
// using namespace Chroma;


// //! Function object used for constructing the time-slice set
// class TimeSliceFunc : public SetFunc {
//   public:
//     TimeSliceFunc(int dir) : dir_decay(dir) {}

//     int operator()(const multi1d<int> &coordinate) const { return coordinate[dir_decay]; }
//     int numSubsets() const { return Layout::lattSize()[dir_decay]; }

//     int dir_decay;

//   private:
//     TimeSliceFunc() {} // hide default constructor
// };



int main(int argc, char const *argv[])
{

    QDP::QDP_initialize(&argc, &argv);

    const int    latdims[Nd] = {32, 32, 32, 32};
    multi1d<int> nrow(4);
    nrow = latdims;
    Layout::setLattSize(nrow);
    Layout::create();

    LatticePropagator propA;
    LatticePropagator propB;

    QDP_volfmt_t volfmt;
    std::string  test_file;



    {
        // volfmt == QDPIO_SINGLEFILE;
        test_file = "/home/Documents/Work/02_LQCDrefs/Chroma/tests/chroma_test/01_io/data/"
                    "propagator/singlefile/propA";

        QDPIO::cout << " ==== File: " << test_file << endl;


        XMLReader     file_in_xml;
        XMLReader     record_in_xml;
        QDPFileReader in(file_in_xml, test_file, QDPIO_PARALLEL);
        // record_in_xml.print();

        QDPIO::cout << " Reader End" << endl;
        in.read(record_in_xml, propA);

        in.close();
    }


    {
        // volfmt == QDPIO_MULTIFILE;
        test_file = "/home/Documents/Work/02_LQCDrefs/Chroma/tests/chroma_test/01_io/data/"
                    "propagator/multifile/propA";

        QDPIO::cout << " ==== File: " << test_file << endl;


        XMLReader     file_in_xml;
        XMLReader     record_in_xml;
        QDPFileReader in(file_in_xml, test_file, QDPIO_PARALLEL);
        // record_in_xml.print();

        QDPIO::cout << " Reader End" << endl;
        in.read(record_in_xml, propB);

        in.close();
    }

    // const int    coords[Nd] = {2, 2, 0, 0};
    // multi1d<int> site(4);
    // site      = coords;
    // int index = Layout::linearSiteIndex(site);
    // QDPIO::cout << " propA(" << index << ")[0,0][0,0] " << propA.elem(index).elem(0, 0).elem(0, 0)
    //             << endl;

    const int G5 = Ns * Ns - 5;

    // LatticePropagator anti_prop = Gamma(G5) * propA * Gamma(G5);

    const int j_decay = Nd - 1;

    Set tSliceSet;
    tSliceSet.make(TimeSliceFunc(j_decay));
    int length = tSliceSet.numSubsets();

    multi1d<Double> MesonPropRealA;
    multi1d<Double> MesonPropRealB;

    // LatticeComplex    latticeCorr = trace(conj(Gamma(G5) * propA * Gamma(G5)) * propA);
    // multi1d<ComplexD> MesonPropC;
    // MesonPropC.resize(length);
    // MesonPropC = sumMulti(latticeCorr, tSliceSet);
    LatticeReal latticeCorrReal;

    {
        latticeCorrReal = real(trace(conj(Gamma(G5) * propA * Gamma(G5)) * propA));
        MesonPropRealA.resize(length);
        MesonPropRealA = sumMulti(real(latticeCorrReal), tSliceSet);
    }

    {
        latticeCorrReal = real(trace(conj(Gamma(G5) * propB * Gamma(G5)) * propB));
        MesonPropRealB.resize(length);
        MesonPropRealB = sumMulti(real(latticeCorrReal), tSliceSet);
    }

    QDPIO::cout << "MesonPropA[t]\tMesonPropB[t]\t T = " << Layout::lattSize()[j_decay] << endl;

    multi1d<Double> mesonDiff = (MesonPropRealA - MesonPropRealB);
    for (int t = 0; t < length; t++) {
        QDPIO::cout << MesonPropRealA[t] << "\t" << MesonPropRealB[t] << "\t" << mesonDiff[t]
                    << endl;
    }

    QDP::QDP_finalize();

    return 0;
}