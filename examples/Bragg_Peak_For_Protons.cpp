#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include "TFile.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TSystem.h"
#include "TMacro.h"
#include <TTree.h>
#include <iostream>
#include <sstream>
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iterator>
#include <algorithm>
#include "TImage.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include <iostream>
#include <cmath>
#include <TLegend.h>


struct Proton{ 
    int par_1,par_2;
    double p_e;
    bool operator != (Proton const & point) const{
    return this->par_1 == point.par_1 && this->par_2 == point.par_2;
}

};

using namespace std;



string GetLocation(string str)
{
     
    int i = str.rfind("_Slot_");
    string way = str.substr(0,i);
    return way;
}

struct vectorsTree
{
  vector<double> *FEBSN;
  vector<double> *SpillTag;
  vector<double> *GTrigTag;
  vector<double> *GTrigTime;
  vector<double> *hitsChannel;
  vector<double> *hitAmpl;
  vector<double> *hitAmplRec;
  vector<double> *hitLGAmpl;
  vector<double> *hitLGAmplRec;
  vector<double> *hitHG_pe;
  vector<double> *hitLG_pe;
  vector<double> *hitToT_pe;
  vector<double> *hitCharge_pe;
  vector<double> *hitLeadTime;
  vector<double> *hitTrailTime;
  vector<double> *hitTimeDif;
  vector<double> *hitTimefromSpill;
  
};

int main ()
{
    //ofstream fout_e("mean_electrons.txt");
    ofstream fout("proton_peak.txt");

    TH1F *CrossTalk_channel_y = new TH1F("CrossTalk for each cube separately ZY","CrossTalk for each cube separately ZY",500,(int)0,(int)20);
    TH1F *CrossTalk_channel_x = new TH1F("CrossTalk for each cube separately XZ","CrossTalk for each cube separately XZ",500,(int)0,(int)20);
    TH1F *CrossTalk_fiber = new TH1F("CrossTalk for X+Y fiber","CrossTalk for X+Y fiber",600,(int)0,(int)40);
    TH1F *CrossTalk_fiber_x = new TH1F("CrossTalk for X fiber","CrossTalk for X fiber",600,(int)0,(int)40);
    TH1F *CrossTalk_fiber_y = new TH1F("CrossTalk for Y fiber","CrossTalk for Y fiber",600,(int)0,(int)40);
    TH2F *CrossTalk = new TH2F("CrossTalk","CrossTalk",  100,(int)0,(int)20, 100,(int)0,(int)25);  
    TH2F *CrossTalk_for_each_event = new TH2F("CrossTalk_for_each_event","CrossTalk_for_each_event",  100,(int)0,(int)100, 600,(int)0,(int)20);  
    int febTrigger = 12;
    int FEBs[19] = {0,1,2,3,4,8,9,10,11,12,16,17,18,19,20,24,25,26,27};
    int NumberOfEB = 30;
    vector<string> vFileNames;
    string sFileName;
    ifstream fList("febs_files_list.list");
    while (!fList.eof()) {
        fList >> sFileName;
        vFileNames.push_back(sFileName);
    }
    fList.close();
    vector <Proton> x_z;
    vector <Proton> x_y;
    vector <Proton> z_y;
    string rootFileInput=GetLocation(vFileNames[0].c_str());
    string rootFileOutput=GetLocation (vFileNames[0].c_str());
    rootFileInput+="_all_reconstructed.root";
    rootFileOutput+="_bragg_peak.root";
    cout << rootFileInput<<endl;
    TFile *FileInput = new TFile(rootFileInput.c_str());
    vectorsTree FEB[NumberOfEB];
    for (Int_t i=0;i<NumberOfEB;i++){
        FEB[i].FEBSN=0;
        FEB[i].SpillTag=0;
        FEB[i].hitsChannel=0;
        FEB[i].hitAmpl=0;
        FEB[i].hitAmplRec=0;
        FEB[i].hitLeadTime=0;
        FEB[i].GTrigTag=0;
        FEB[i].GTrigTime=0;
        FEB[i].hitLGAmpl=0;
        FEB[i].hitLGAmplRec=0;
        FEB[i].hitTrailTime=0;
        FEB[i].hitTimeDif=0;
        FEB[i].hitTimefromSpill=0;
        
        FEB[i].hitHG_pe=0;
        FEB[i].hitLG_pe=0;
        FEB[i].hitToT_pe=0;
        FEB[i].hitCharge_pe=0;
        
    }
    
    TTree *FEBtree[NumberOfEB];
    Long64_t nentries[NumberOfEB];
    std::fill(nentries, nentries + NumberOfEB, 0);   
    ostringstream sFEBnum;
    string sFEB;
    vector<int> FEBnumbers;
    FEBnumbers.clear();
    // int NumberEvDis = 500;

    for (Int_t ih=0; ih<NumberOfEB; ih++) {
        sFEBnum.str("");
        sFEBnum << ih;
        sFEB = "FEB_"+sFEBnum.str();
        FEBtree[ih] = (TTree*)FileInput->Get(sFEB.c_str());
        if ((TTree*)FileInput->Get(sFEB.c_str())){
            //std::cout<<sFEB<<" ";
            FEBtree[ih]->SetBranchAddress((sFEB+"_SN").c_str(),&FEB[ih].FEBSN);
            FEBtree[ih]->SetBranchAddress((sFEB+"_SpillTag").c_str(),&FEB[ih].SpillTag);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTag").c_str(),&FEB[ih].GTrigTag);
            FEBtree[ih]->SetBranchAddress((sFEB+"_GTrigTime").c_str(),&FEB[ih].GTrigTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitsChannel").c_str(),&FEB[ih].hitsChannel);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitAmpl").c_str(),&FEB[ih].hitAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLGAmpl").c_str(),&FEB[ih].hitLGAmpl);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLeadTime").c_str(),&FEB[ih].hitLeadTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTrailTime").c_str(),&FEB[ih].hitTrailTime);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimeDif").c_str(),&FEB[ih].hitTimeDif);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitTimefromSpill").c_str(),&FEB[ih].hitTimefromSpill);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitAmplRecon").c_str(), &FEB[ih].hitAmplRec);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLGAmplRecon").c_str(), &FEB[ih].hitLGAmplRec);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitHG_pe").c_str(), &FEB[ih].hitHG_pe);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitLG_pe").c_str(), &FEB[ih].hitLG_pe);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitToT_pe").c_str(), &FEB[ih].hitToT_pe);
            FEBtree[ih]->SetBranchAddress((sFEB+"_hitCharge_pe").c_str(), &FEB[ih].hitCharge_pe);
            
            nentries[ih] = FEBtree[ih]->GetEntries();
            FEBtree[ih]->GetEntry(0);
            //cout << "Number of events = " <<FEB[ih].FEBSN->size()<<std::endl;
        }
    }
    int minEn = (int)nentries[0];
    for(int i = 0; i < NumberOfEB; i++){
        if(nentries[i] < minEn && nentries[i]>0) minEn = (int)nentries[i];
    }
    cout << "Number of spills " << minEn << endl;

    TFile wfile(rootFileOutput.c_str(), "recreate");
    TDirectory *events2D = wfile.mkdir("events2D");
    TDirectory *events2D_bad = wfile.mkdir("events2D_bad");
    cout<<rootFileOutput<<endl;
    int MapCon[28][2][96];
    for (int iFEB = 0; iFEB<19; iFEB++) {
       if (FEBs[iFEB] != febTrigger){
            sFEBnum.str("");
            sFEBnum << FEBs[iFEB];
            sFEB = "../mapping/" + sFEBnum.str() + ".txt";
            ifstream fmap(sFEB.c_str());
            //cout <<endl<< "FEB "<< FEBs[iFEB]<< " mapping"<<endl;
            int temp=0;
            while (!fmap.eof()) {
                fmap >> temp >> MapCon[FEBs[iFEB]][0][temp] >> MapCon[FEBs[iFEB]][1][temp];
            //cout<<temp<<" "<<MapCon[FEBs[iFEB]][0][temp]<<" "<<MapCon[FEBs[iFEB]][1][temp]<<endl;
                temp++;
            }
            fmap.close();
       }
    }

    ostringstream sEventnum;
    string sEvent;

    TH1F *events2D_LY_XZ_YZ[48];
    for (Int_t ih=0; ih < 48;ih++){
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_XZ&YZ_LY"+sEventnum.str();
        events2D_LY_XZ_YZ[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(), 70,(int)0,(int)1000);
    }

    TH1F *events2D_Iterator[48];
    for (Int_t ih=0; ih < 48;ih++){
        sEventnum.str("");
        sEventnum << ih;
        sEvent = "event_Iterator"+sEventnum.str();
        events2D_Iterator[ih] = new TH1F(sEvent.c_str(),sEvent.c_str(), 70,(int)0,(int)1500);
    }

    Double_t energyDep[48];
    Double_t energyDepXZ[48];
    Double_t energyDepYZ[48];

    TH2F *event_XY;
        sEventnum.str("");
        sEvent = "event_XY"+sEventnum.str();
        event_XY = new TH2F(sEvent.c_str(),sEvent.c_str(), 24,(int)0,(int)24, 8,(int)0,(int)8);

    TH2F *event_YZ;
        sEventnum.str("");
        sEvent = "event_YZ"+sEventnum.str();
        event_YZ = new TH2F(sEvent.c_str(),sEvent.c_str(), 48,(int)0,(int)48, 8,(int)0,(int)8);

    TH2F *event_XZ;
        sEventnum.str("");
        sEvent = "event_XZ"+sEventnum.str();
        event_XZ = new TH2F(sEvent.c_str(),sEvent.c_str(), 24,(int)0,(int)24, 48,(int)0,(int)48);
  
    TH1F *event_LY;
        sEventnum.str("");
        sEvent = "event_LY"+sEventnum.str();
        event_LY = new TH1F(sEvent.c_str(),sEvent.c_str(),48,(int)0,(int)48);

    TH1F *event_Time;
        sEventnum.str("");
        sEvent = "event_Time"+sEventnum.str();
        event_Time = new TH1F(sEvent.c_str(),sEvent.c_str(),4000,(int)0,(int)4000);
  
    vector<int> time;

    TH2F *EventsMap_EnergyDeposit = new TH2F("EnergyDeposit_2D","EnergyDeposit_2D",  48,(int)0,(int)48, 200,(int)0,(int)900);

    TH1F *trigger_Time;
        trigger_Time = new TH1F(sEvent.c_str(),sEvent.c_str(),4000,(int)0,(int)4000);
        sEventnum.str("");
    int ev_num = 0;
    // sEventnum << ih;
    sEvent = "trigger_Time"+sEventnum.str();
    Int_t eventNum=0;
    bool LargehitTimeDif = 0;
    TCanvas *c1 = new TCanvas("c1","c1", 1480, 1160);
    bool SpillMised = false;
    for (Int_t subSpill = 0; subSpill<minEn; subSpill++) {
        Int_t SpillNumber = subSpill;
        cout << "Getting Spill Number " << SpillNumber + 1 << endl;
        for (int ik = 0; ik < 19; ik++){
            FEBtree[FEBs[ik]]->GetEntry(SpillNumber);
            if (FEB[FEBs[ik]].SpillTag->back() != SpillNumber + 1) break;
            if (FEB[FEBs[ik]].SpillTag->size() < 2  ){
                cout << "NULL"<<endl;
                SpillMised = true;
                break;
            } else {
                SpillMised = false;
            }
            //cout << "FEB_"<< FEBs[ik]<< " "<< FEB[FEBs[ik]].hitCharge_pe->size()<<endl;
        }
        if (!SpillMised){

            for ( int TOFtrigger = 0; TOFtrigger < FEB[febTrigger].FEBSN->size(); TOFtrigger++){
                if (FEB[febTrigger].hitTimeDif->at(TOFtrigger) > 0 /*&& NumberEvDis > eventNum */ && FEB[febTrigger].hitsChannel->at(TOFtrigger) == 2){
                    bool triggerDisplay = false;
                    LargehitTimeDif = 0;
                    Double_t Cross = 0;
                    Int_t GTindex[2] = {0,0};
                    for (int ik = 0; ik < 48; ik++ ){
                        energyDep[ik] = 0;
                        energyDepXZ[ik] = 0;
                        energyDepYZ[ik] = 0;
                    }

                    for (int i = 0; i < 19; i++){
                        if (FEBs[i]!=febTrigger){
                            auto bounds=std::equal_range (FEB[FEBs[i]].GTrigTag->begin(), FEB[FEBs[i]].GTrigTag->end(), FEB[febTrigger].GTrigTag->at(TOFtrigger));
                            GTindex[0] = bounds.first - FEB[FEBs[i]].GTrigTag->begin();
                            GTindex[1] = bounds.second - FEB[FEBs[i]].GTrigTag->begin();
            
                            for (int check = GTindex[0]; check <  GTindex[1]; check++){
                                if ( (FEB[febTrigger].hitTimefromSpill->at(TOFtrigger) - FEB[FEBs[i]].hitTimefromSpill->at(check)) > 40 &&
                                    (FEB[febTrigger].hitTimefromSpill->at(TOFtrigger) - FEB[FEBs[i]].hitTimefromSpill->at(check)) < 120){
                                    if (FEB[FEBs[i]].hitTimeDif->at(check) > 50) LargehitTimeDif = 1;
                                    if ( FEBs[i] == 0 || FEBs[i] == 16){
                                         event_XY->Fill((int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],(int)MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check));
                                        if(FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000)
                                            x_y.push_back({(int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],(int)MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check)});
                                        event_Time->Fill((int)FEB[FEBs[i]].hitLeadTime->at(check));
                                        time.push_back((int)FEB[FEBs[i]].hitLeadTime->at(check));
                                        if (!triggerDisplay){
                                            trigger_Time->Fill(FEB[febTrigger].hitLeadTime->at(TOFtrigger));
                                            triggerDisplay = true;
                                        }
                                    } else if ( FEBs[i] == 1 || FEBs[i] == 2 || FEBs[i] == 17 || FEBs[i] == 24){
                                        event_YZ->Fill((int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],(int)MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check));
                                        event_Time->Fill((int)FEB[FEBs[i]].hitLeadTime->at(check));
                                        time.push_back((int)FEB[FEBs[i]].hitLeadTime->at(check));             
                                        if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000) {
                                            z_y.push_back({(int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],(int)MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check)});
                                            energyDep[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                            energyDepYZ[MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        }
                                        if (MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] == 0 || MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)] == 7){
                                            Cross  += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        }
                                    } else {

                                        event_XZ->Fill((int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],(int)MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check));
                                        event_Time->Fill((int)FEB[FEBs[i]].hitLeadTime->at(check));
                                        time.push_back((int)FEB[FEBs[i]].hitLeadTime->at(check));
                                        if (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000){
                                            x_z.push_back({(int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)],(int)MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)],FEB[FEBs[i]].hitCharge_pe->at(check)});
                                            energyDep[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                            energyDepXZ[MapCon[FEBs[i]][1][(int)FEB[FEBs[i]].hitsChannel->at(check)]] += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        }
                                        if ((int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] == 0 || (int)MapCon[FEBs[i]][0][(int)FEB[FEBs[i]].hitsChannel->at(check)] == 23){
                                            Cross  += FEB[FEBs[i]].hitCharge_pe->at(check);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    for (int ik = 0; ik < 40; ik++ ){
                        if (energyDepXZ[ik] > 5 && energyDepXZ[ik+2] > 5 && energyDepXZ[ik+4] > 5 && energyDepXZ[ik+6] > 5 &&
                            energyDepXZ[ik+1] < 5 && energyDepXZ[ik+3] < 5 && energyDepXZ[ik+5] < 5 && energyDepXZ[ik+7] < 5)
                            LargehitTimeDif = 1;

                        if (energyDepYZ[ik] > 5 && energyDepYZ[ik+2] > 5 && energyDepYZ[ik+4] > 5 && energyDepYZ[ik+6] > 5 &&
                            energyDepYZ[ik+1] < 5 && energyDepYZ[ik+3] < 5 && energyDepYZ[ik+5] < 5 && energyDepYZ[ik+7] < 5)
                            LargehitTimeDif = 1;                           
                    }

                    if ( LargehitTimeDif == 0) {
                        c1->Clear();
                        if (event_XZ->GetEntries()>5 && event_YZ->GetEntries()>5 /*&& CrossTalk < 60*/){

                            auto p_e_max = max_element(z_y.begin(),z_y.end(),[] (const auto &x, const auto &y){return x.p_e < y.p_e;});
                            int z_stop = p_e_max->par_1;
                            int y_stop = p_e_max->par_2;
                            Double_t max_en_y = p_e_max->p_e;
                            int z_max = max_element(z_y.begin(),z_y.end(),[] (const auto &x, const auto &y){return x.par_1 < y.par_1;})->par_1;
                            p_e_max = max_element(x_z.begin(),x_z.end(),[] (const auto &x, const auto &y){return x.p_e < y.p_e;});
                            int x_stop = p_e_max->par_1;
                            int z_stop_x_z = p_e_max->par_2;
                            Double_t max_en_x = p_e_max->p_e;
                            p_e_max = max_element(x_y.begin(),x_y.end(),[] (const auto &x, const auto &y){return x.p_e< y.p_e;});
                            int x_stop_x_y = p_e_max->par_1;
                            int y_stop_x_y = p_e_max->par_2;
                            int bin = event_Time->GetMaximumBin();
                            int x = event_Time->GetXaxis()->GetBinCenter(bin);
                            int time_max = *max_element(time.begin(),time.end());
                            Double_t CrossTalk_1 = 0;
                            Double_t CrossTalk_3 = 0;
                            Proton res_y = {0,0,0};
                            Proton res_x = {0,0,0};
                            if( event_YZ->GetEntries()>6 && z_max < 45 &&event_YZ->GetEntries() < 100 && event_XZ->GetEntries() < 100 && FEB[febTrigger].hitLeadTime->at(TOFtrigger) - time_max  > 60 && FEB[febTrigger].hitLeadTime->at(TOFtrigger) - x  < 110 && y_stop!=0 && y_stop!= 7 && Cross < 60  && z_stop > 2){
                                Double_t p_e_max = max_en_y/1.2;
                                for(auto i : z_y){
                                    if(i.p_e > p_e_max && abs(i.par_2 - y_stop) < 2 && abs(i.par_1 - z_stop) < 2 && (i.par_2 != y_stop ||i.par_1 != z_stop)){
                                        if((abs(i.par_2 - res_y.par_2)>0 && i.par_2 != y_stop)||res_y.p_e == 0)  res_y = {i.par_1,i.par_2,i.p_e};
                                    }
                                }
                                for(auto i : z_y){
                                    if(i.p_e < p_e_max/4.5){
                                        if(abs(i.par_2 - y_stop) < 2 && i.par_1 == z_stop && i.par_2 != y_stop ){
                                            CrossTalk_1 += i.p_e/max_en_y*100 ;
                                            CrossTalk_channel_y->Fill(i.p_e/max_en_y*100);
                                            CrossTalk_for_each_event->Fill(ev_num,i.p_e/max_en_y*100,1);
                                        }
                                        if(res_y.p_e != 0){
                                            if(abs(i.par_2 - res_y.par_2) < 2 && i.par_1 == res_y.par_1 && i.par_2 != res_y.par_2){
                                                CrossTalk_1 += i.p_e/res_y.p_e*100;
                                                CrossTalk_channel_y->Fill(i.p_e/res_y.p_e*100);
                                                CrossTalk_for_each_event->Fill(ev_num,i.p_e/res_y.p_e*100,1);
                                            }
                                        }
                                    }
                                }

                                p_e_max = max_en_x / 1.2;

                                for(auto i : x_z){
                                    if(i.p_e > p_e_max && abs(i.par_1 - x_stop) < 2 && abs(i.par_2 - z_stop_x_z) < 2 && (i.par_1 != x_stop ||i.par_2 != z_stop_x_z)){
                                        if((abs(i.par_1 - res_x.par_1)>0 && i.par_1 != x_stop)||res_x.p_e == 0)  res_x = {i.par_1,i.par_2,i.p_e};
                                    }
                                }   
                                for(auto i : x_z){
                                    if(i.p_e < p_e_max /4.5){
                                        if(abs(i.par_1 - x_stop) < 2 && i.par_2 == z_stop_x_z && i.par_1 != x_stop){
                                            CrossTalk_3 += i.p_e/max_en_x*100;
                                            CrossTalk_channel_x->Fill(i.p_e/max_en_x*100);
                                            CrossTalk_for_each_event->Fill(ev_num,i.p_e/max_en_x*100,1);
                                        }
                                        if(res_x.p_e != 0){
                                            if(abs(i.par_1 - res_x.par_1) < 2 && i.par_2 == res_x.par_2 && i.par_1 != res_x.par_1){
                                                CrossTalk_3 += i.p_e/res_x.p_e*100;
                                                CrossTalk_channel_x->Fill(i.p_e/res_x.p_e*100);
                                                CrossTalk_for_each_event->Fill(ev_num,i.p_e/res_x.p_e*100,1);
                                            }
                                        }
                                    }
                                } 
                                ++ev_num;
                                c1->Divide(3,2);
                                
                                c1 -> cd(1);
                                event_XY-> GetYaxis()->SetTitle("Y [cm]");
                                event_XY-> GetXaxis()->SetTitle("X [cm]");
                                string name_1 = "Stop: x = "+ to_string(x_stop_x_y)+", y = " +to_string(y_stop_x_y);
                                event_XY-> SetTitle(name_1.c_str());
                                event_XY-> Draw("colorz");
        
                                c1 -> cd(2);
                                event_YZ-> GetYaxis()->SetTitle("Y [cm]");
                                event_YZ-> GetXaxis()->SetTitle("Z [cm]");
                                string s = to_string(eventNum);
                                string name_2 = s +":  y = "+ to_string(y_stop)+", z = " +to_string(z_stop);
                                event_YZ-> SetTitle(name_2.c_str());
                                event_YZ-> Draw("colorz");
        
                                c1 -> cd(3);
                                event_XZ-> GetYaxis()->SetTitle("Z [cm]");
                                event_XZ-> GetXaxis()->SetTitle("X [cm]");
                                string name_3 = "Stop: z = "+ to_string(z_stop_x_z)+", x = " +to_string(x_stop);
                                event_XZ-> SetTitle(name_3.c_str());
                                event_XZ->Draw("colorz");


                                c1 -> cd(4);
                                event_LY-> GetYaxis()->SetTitle("LY [p.e.] (X+Y fiber)");
                                event_LY-> GetXaxis()->SetTitle("Z [cm]");
                                event_LY->Draw("HIST");
        
                                c1 -> cd(5);
                                if(FEB[febTrigger].hitsChannel->at(TOFtrigger) == 0) event_Time->SetTitle("Electrons");
                                if(FEB[febTrigger].hitsChannel->at(TOFtrigger) == 1) event_Time->SetTitle("Muons/Pions");
                                if(FEB[febTrigger].hitsChannel->at(TOFtrigger) == 2) event_Time->SetTitle("Protons");
                                event_Time-> GetYaxis()->SetTitle("N");
                                event_Time-> GetXaxis()->SetTitle("T [2.5 ns]");
                                trigger_Time->SetLineColor(kRed);
                                trigger_Time->Draw("SAME");
                                event_Time->Draw();

                                c1 -> cd(6);
                                trigger_Time->Draw("SAME");

                                c1->Update();

                                if(z_max > z_stop + 5 || eventNum == 2625 )
                                    events2D_bad -> cd();                       
                                else{
                                    events2D -> cd();
                                    CrossTalk->Fill(CrossTalk_1,CrossTalk_3,1);
                                    for (int ik = 0; ik < 48; ik++ ){
                                        if (energyDep[ik]>20)
                                            EventsMap_EnergyDeposit->Fill(ik-z_stop+45,energyDep[ik],1);
                                    }

                                    CrossTalk_fiber ->Fill(CrossTalk_1+CrossTalk_3);
                                    CrossTalk_fiber_y ->Fill(CrossTalk_1);
                                    CrossTalk_fiber_x ->Fill(CrossTalk_3);
                                }

                                c1->Write();
                            }
                        }   
                    }
                    event_Time->Reset();
                    trigger_Time->Reset();
                    event_XY->Reset();
                    event_YZ->Reset();
                    event_XZ->Reset();
                    event_LY->Reset();
                    z_y.clear();
                    x_y.clear();
                    x_z.clear();
                    time.clear();
                    eventNum++;
                }
            }
        }
    }
    cout << eventNum;
    wfile.cd();
    c1->cd();
    EventsMap_EnergyDeposit->GetYaxis()->SetTitle("LY [p.e.] (X+Y fiber)");
    EventsMap_EnergyDeposit->GetXaxis()->SetTitle("Z [cm]");
    EventsMap_EnergyDeposit->Draw("colorz");
    c1->Write();
    c1->Clear();
    CrossTalk->GetYaxis()->SetTitle("XZ[p.e.] as a %");
    //CrossTalk->GetYaxis()->SetTitle("XZ[p.e.]");
    //CrossTalk->GetXaxis()->SetTitle("ZY[p.e.]");
    CrossTalk->GetXaxis()->SetTitle("ZY[p.e.] as a %");
    CrossTalk->Draw("colorz");
    c1->Write();

    c1->Clear();
    CrossTalk_for_each_event->GetYaxis()->SetTitle("p.e. as a %");
    //CrossTalk_for_each_event->GetYaxis()->SetTitle("p.e.");
    CrossTalk_for_each_event->GetXaxis()->SetTitle("Event");
    CrossTalk_for_each_event->Draw("colorz");
    c1->Write();
    c1->Clear();
    TF1 *fit = new TF1("fit","gaus"); 
    CrossTalk_fiber->Fit("fit");
    CrossTalk_fiber->GetYaxis()->SetTitle("N");
    CrossTalk_fiber->GetXaxis()->SetTitle("[p.e.] as a %");
    //CrossTalk_fiber->GetXaxis()->SetTitle("[p.e.]");
    CrossTalk_fiber->Draw("colorz");
    c1->Write();
    c1->Clear();
    CrossTalk_fiber_x->Fit("fit");
    CrossTalk_fiber_x->GetYaxis()->SetTitle("N");
    CrossTalk_fiber_x->GetXaxis()->SetTitle("[p.e.] as a %");
    //CrossTalk_fiber->GetXaxis()->SetTitle("[p.e.]");
    CrossTalk_fiber_x->Draw("colorz");
    c1->Write();
    c1->Clear();
    CrossTalk_fiber_y->Fit("fit");
    CrossTalk_fiber_y->GetYaxis()->SetTitle("N");
    CrossTalk_fiber_y->GetXaxis()->SetTitle("[p.e.] as a %");
    //CrossTalk_fiber->GetXaxis()->SetTitle("[p.e.]");
    CrossTalk_fiber_y->Draw("colorz");
    c1->Write();
    c1->Clear();
    CrossTalk_channel_x->Fit("fit");
    CrossTalk_channel_x->GetYaxis()->SetTitle("N");
    CrossTalk_channel_x->GetXaxis()->SetTitle("[p.e.] as a %");
    //CrossTalk_channel_x->GetXaxis()->SetTitle("[p.e.]");
    CrossTalk_channel_x->Draw("colorz");
    c1->Write();
    c1->Clear();

    CrossTalk_channel_y->Fit("fit");
    CrossTalk_channel_y->GetYaxis()->SetTitle("N");
    CrossTalk_channel_y->GetXaxis()->SetTitle("[p.e.] as a %");
    //CrossTalk_channel_x->GetXaxis()->SetTitle("[p.e.]");
    CrossTalk_channel_y->Draw("colorz");
    c1->Write();
    c1->Clear();
    wfile.Close();
    FileInput->Close();
    return 0;
}

// see /..bragg_peak.root