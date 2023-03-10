message(STATUS "examples ... ")

ADD_EXECUTABLE(dump         babyMindDataDump.cpp)
TARGET_LINK_LIBRARIES(dump  BabyMINDUnpack)

ADD_EXECUTABLE(pid_vs_tof         out_vs_pid.cpp)

if    (ROOT_FOUND)
  ADD_EXECUTABLE(unpack                             babyMindUnpack.cpp)
  TARGET_LINK_LIBRARIES(unpack                      BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(ufe-monitor                        ufe_monitor.cpp)
  TARGET_LINK_LIBRARIES(ufe-monitor                 BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(TDMunpack                          babyMINDTDMUnpack.cpp)
  TARGET_LINK_LIBRARIES(TDMunpack                   BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(GTrigTagSearch                     GTrigTagSearch.cpp)
  TARGET_LINK_LIBRARIES(GTrigTagSearch              BabyMINDUnpack ${ROOT_LIBRARIES})
  
  ADD_EXECUTABLE(HG_vs_LG_calib                     HG_LG_calib.cpp)
  TARGET_LINK_LIBRARIES(HG_vs_LG_calib              BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(HG_vs_ToT_calib                    HG_vs_ToT_calib.cpp)
  TARGET_LINK_LIBRARIES(HG_vs_ToT_calib             BabyMINDUnpack ${ROOT_LIBRARIES})
  
  ADD_EXECUTABLE(LG_vs_ToT_calib                    LG_vs_ToT_calib.cpp)
  TARGET_LINK_LIBRARIES(LG_vs_ToT_calib             BabyMINDUnpack ${ROOT_LIBRARIES})
  
  ADD_EXECUTABLE(HG_reconstructed                   HG_reconstructed_obso.cpp)
  TARGET_LINK_LIBRARIES(HG_reconstructed            BabyMINDUnpack ${ROOT_LIBRARIES})
  
  ADD_EXECUTABLE(RootFileAnalyssis_recon            t9rootFileanalysis_recon.cpp)
  TARGET_LINK_LIBRARIES(RootFileAnalyssis_recon     BabyMINDUnpack ${ROOT_LIBRARIES})
  
  ADD_EXECUTABLE(StoppingProton                     Proton_stop.cpp)
  TARGET_LINK_LIBRARIES(StoppingProton              BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(MuonStop                           Muon_stop.cpp)
  TARGET_LINK_LIBRARIES(MuonStop                    BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(Calibration                        babyMindCalibration.cpp)
  TARGET_LINK_LIBRARIES(Calibration                 BabyMINDUnpack "${ROOT_LIBRARIES} -lSpectrum")

  ADD_EXECUTABLE(Amplitude_matching                 BabyMIND_ToT_Amplitude_matching.cpp)
  TARGET_LINK_LIBRARIES(Amplitude_matching          BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(AverageLY                          AverageLY.cpp)
  TARGET_LINK_LIBRARIES(AverageLY                   BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(AverageLY_August                   AverageLY_August.cpp)
  TARGET_LINK_LIBRARIES(AverageLY_August            BabyMINDUnpack ${ROOT_LIBRARIES})

  ADD_EXECUTABLE(ProtonStop                         Max_LY_XZvsYZ.cpp)
  TARGET_LINK_LIBRARIES(ProtonStop                  BabyMINDUnpack ${ROOT_LIBRARIES})
  
endif (ROOT_FOUND)
