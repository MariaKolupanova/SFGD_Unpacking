#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <TTree.h>
// #include "TDirectory.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TMacro.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TGraphErrors.h"
using namespace std;

string GetLocation(string str)
{
     
    int i = str.rfind("_Slot_");
    string way = str.substr(0,i);
    return way;
}

Double_t fpeaks(Double_t *x, Double_t *par) {
    return -par[0]*log(1/(par[1]-x[0]))+par[2]/(x[0]-par[3])+par[4];}
    // return -par[0]*log(1/(par[1]-x[0]))+par[2]/(x[0]*x[0]-par[3])+par[4];} // for electrons and protons

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

     int main(){
    int febTrigger = 12;
    int FEBs[19] = {0,1,2,3,4,8,9,10,11,12,16,17,18,19,20,24,25,26,27};
    int NumberOfEB = 30;
    string sFileName, line;
    // 0 - electrons / 1 - muons / 2 - protons - choose the type of particle to calibrate
    // for protons and electrons change fit function and time from trigger in the end of this file
    int trigger = 1;
    ifstream fList("febs_files_list.list"); 
    vector<string> vFileNames;
    while (!fList.eof()) {
        fList >> sFileName;
        vFileNames.push_back(sFileName);
    }
    fList.close();
    string rootFileInput=GetLocation(vFileNames[0].c_str()) + "_all_reconstructed.root";;
    string txtFileInput=GetLocation (vFileNames[0].c_str()) + "_graph.txt";
    string txtFileOutput=GetLocation (vFileNames[0].c_str())+ "_parameters.txt";
    ifstream in(txtFileInput);
    ofstream out(txtFileOutput);
    TFile wfile((GetLocation (vFileNames[0].c_str())+"_time_from_trigger.root").c_str(), "recreate");
    TH1F* h[40];
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
    vector<pair<int,double>> Time_P_e;
    vector<int> FEBnumbers;
    FEBnumbers.clear();
    // int NumberEvDis = 50;

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
        }
    }
    int minEn = (int)nentries[0];
    for(int i = 0; i < NumberOfEB; i++){
        if(nentries[i] < minEn && nentries[i]>0) minEn = (int)nentries[i];
    }
    cout << "Number of spills " << minEn << endl;
    int MapCon[28][2][96];
    for (int iFEB = 0; iFEB<19; iFEB++) {
       if (FEBs[iFEB] != febTrigger){
            sFEBnum.str("");
            sFEBnum << FEBs[iFEB];
            sFEB = "../mapping/" + sFEBnum.str() + ".txt";
            ifstream fmap(sFEB.c_str());
            int temp=0;
            while (!fmap.eof()) {
                fmap >> temp >> MapCon[FEBs[iFEB]][0][temp] >>MapCon[FEBs[iFEB]][1][temp];
                temp++;
            }
            fmap.close();
       }
    }
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
                if (FEB[febTrigger].hitTimeDif->at(TOFtrigger) > 0 /*&& NumberEvDis > eventNum */ && FEB[febTrigger].hitsChannel->at(TOFtrigger) == trigger){
                    Int_t GTindex[2] = {0,0};
                    for (int i = 0; i < 19; i++){
                        if (FEBs[i]!=febTrigger){
                            auto bounds=std::equal_range (FEB[FEBs[i]].GTrigTag->begin(), FEB[FEBs[i]].GTrigTag->end(), FEB[febTrigger].GTrigTag->at(TOFtrigger));
                            GTindex[0] = bounds.first - FEB[FEBs[i]].GTrigTag->begin();
                            GTindex[1] = bounds.second - FEB[FEBs[i]].GTrigTag->begin();
            
                            for (int check = GTindex[0]; check <  GTindex[1]; check++){
                                if ( (FEB[febTrigger].hitTimefromSpill->at(TOFtrigger) - FEB[FEBs[i]].hitTimefromSpill->at(check)) > 40 &&
                                    (FEB[febTrigger].hitTimefromSpill->at(TOFtrigger) - FEB[FEBs[i]].hitTimefromSpill->at(check)) < 120 &&
                                    (FEB[FEBs[i]].hitCharge_pe->at(check) > 0  && FEB[FEBs[i]].hitCharge_pe->at(check) < 10000)){
                                        Double_t par_x = (int)FEB[FEBs[i]].hitLeadTime->at(check) - FEB[febTrigger].hitLeadTime->at(TOFtrigger);
                                        Double_t par_y = (Double_t)FEB[FEBs[i]].hitCharge_pe->at(check);
                                        Time_P_e.push_back({par_x,par_y});
                                        // cout <<par_x<<" "<<par_y<<endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    wfile.cd();
    for (int i=0;i<40;i++){
    string sEvent = "event_Iterator"+to_string(i);
     h[i]= new TH1F("Protons", sEvent.c_str(),500,(int)0,(int)500);
    }
    TCanvas *c = new TCanvas("c","c",10,10,1900,1000); 
    int j = 0;
    int m = 0;
    int time = 0;
    double min = 10;
    double max = 0;
    sort(Time_P_e.begin(),Time_P_e.end(),[](const auto& p1, const auto& p2){return p1.first < p2.first;});
    time = 0;
     TGraphErrors* g = new TGraphErrors();
    for(pair<int,double> t_p_e : Time_P_e){
        if(time!= t_p_e.first && time!=0 && t_p_e.first >= -120/*&& t_p_e.first <= -85*/&& t_p_e.first <= -100) {
            int binmax = h[j]->GetMaximumBin();
            double a = h[j]->GetXaxis()->GetBinCenter(binmax);
                TF1 *fit = new TF1("fit","gaus"); 
                int n_entries = h[j]->GetEntries();
                //trigger = 1
                if(n_entries > 30000){

                    h[j]->Fit("fit","","",0,a+60);
                    h[j]->Write();
                    double perem_1 = fit->GetParameter("Mean");
                    double perem_2 = fit->GetParError(1);
                //if(perem_1 >0 /*&& perem_2<perem_1*/&&(t+119<20)){
                    g->AddPoint(perem_1,time+120);
                    g->SetPointError(m,perem_2,0);
                    m+=1;
                    if(max < perem_1) max = perem_1;
                    if(min> perem_1) min = perem_1;

                }
                delete h[j];
                j+=1;
            }
        h[j]->Fill(t_p_e.second);
        time = t_p_e.first;
    }
    c->cd();
    g->SetMarkerColor(4);
    g->SetTitle("Fit");
    g->GetXaxis()->SetTitle("Photoelectrons");
    g->GetYaxis()->SetTitle("T [2.5 ns]");
    TF1 *f = new TF1("f",fpeaks,min - 1,max+2,5); 
    f->SetParameters(2.4,57,1,4.2,0);
    f->SetParLimits(0,2,3);
    f->SetParLimits(1,56.5,60);
    f->SetParLimits(2,0.5,2);
    f->SetParLimits(3,2,5);
    f->SetParLimits(4,-1,2);
    g->Fit("f","","",min - 2,max+2);
    g->Draw("AP");
    c->Write();
    cout << min<<" "<<max<<endl;
    Double_t par[5];
    f->GetParameters(&par[0]);
    for(int m = 0;m<5;m++) out <<par[m]<<" ";
    out<<endl;

    delete g;
    return 0;
}
