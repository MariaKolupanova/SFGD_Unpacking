./TDMunpack -f ../../../../t2k/data/sFGD/CERN_2018/1September_20/1September_20_MCR0_muons_2Gev_0pt2T_4trigg_0deg__.daq
./TDMunpack -f ../../../../t2k/data/sFGD/CERN_2018/1September_20/1September_20_MCR1_muons_2Gev_0pt2T_4trigg_0deg__.daq
./TDMunpack -f ../../../../t2k/data/sFGD/CERN_2018/1September_20/1September_20_MCR2_muons_2Gev_0pt2T_4trigg_0deg__.daq
./TDMunpack -f ../../../../t2k/data/sFGD/CERN_2018/1September_20/1September_20_MCR3_muons_2Gev_0pt2T_4trigg_0deg__.daq
ls -1 ../../../../t2k/data/sFGD/CERN_2018/1September_20/1September_20_MCR*Slot* > febs_files_list.list
./unpack -f d
./Amplitude_matching 