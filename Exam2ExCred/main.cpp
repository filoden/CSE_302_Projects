#include "AUList.h"
#include "ASList.h"
#include "BST.h"
#include "LLSList.h"
#include "LLUList.h"

#include <chrono>
#include <random>
#include <iostream>
#include <cmath>

using namespace std;

struct tableEntry {
    double aulistinsert[3];
    double aslistinsert[3];
    double llulistinsert[3];
    double llslistinsert[3];
    double bstreeinsert[3];
    double aulistsearch[3];
    double aslistsearch[3];
    double llulistsearch[3];
    double llslistsearch[3];
    double bstreesearch[3];
    double aulistdelete[3];
    double aslistdelete[3];
    double llulistdelete[3];
    double llslistdelete[3];
    double bstreedelete[3];
};

tableEntry results[10];

template <typename ItemType>
double functionTimerinsert(ItemType& obj, void (ItemType::*func)(int), int param) {
    auto start = std::chrono::high_resolution_clock::now();
    (obj.*func)(param);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration = end - start;
    return duration.count();
}

template <typename ItemType>
double functionTimerSearch(ItemType& obj, int (ItemType::*func)(int), int param) {
    auto start = std::chrono::high_resolution_clock::now();
    (obj.*func)(param);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration = end - start;
    return duration.count();
}

template <typename ItemType>
double functionTimerSearch(ItemType& obj, int (ItemType::*func)(int, bool&) const, int param) {
    auto start = std::chrono::high_resolution_clock::now();
    bool found;
    obj.GetItem(param, found);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration = end - start;
    return duration.count();
}

int* arraygen() {
    int *arr = new int[500];
    for (int i = 0; i < 500; ++i) {
        arr[i] = rand();
    }
    
    //cout << "\nResolving duplicates in array...\nArray length is:   0";
    while (true) {
        
        for (int i = 0; i < 500; ++i) {
            /*
            if (i<10){
                cout << "\b" << i+1;
            }
            else if (i<100){
                cout << "\b\b" << i+1;
            }
            else{
                cout << "\b\b\b" << i+1;
            }
            */
            for (int j = i + 1; j < 500; ++j) {
                if (arr[i] == arr[j]) {
                    arr[j] = rand();
                    continue;
                }
            }
            
            arr[i] = rand();
        }
        break;
    }
    return arr;
}

void InsertAnalysis(int array[], tableEntry* entry){
    AUList aulist;
    ASList aslist(500);
    LLUList lluist;
    LLSList llslist;
    TreeType bstree;

    double aulistinserttimes[500];
    double aslistinserttimes[500];
    double llulistinserttimes[500];
    double llslistinserttimes[500];
    double bstreeinserttimes[500];

    for (int i = 0; i < 500; ++i) {
        aulistinserttimes[i] = functionTimerinsert<AUList>(aulist, (AUList::PutItem), array[i]);
        aslistinserttimes[i] = functionTimerinsert<ASList>(aslist, (ASList::PutItem), array[i]);
        llulistinserttimes[i] = functionTimerinsert<LLUList>(lluist, (LLUList::PutItem), array[i]);
        llslistinserttimes[i] = functionTimerinsert<LLSList>(llslist, (LLSList::PutItem), array[i]);
        bstreeinserttimes[i] = functionTimerinsert<TreeType>(bstree, (TreeType::PutItem), array[i]);
    }

    double averageaulistinserttime = 0.0;
    double averageaslistinserttime = 0.0;
    double averagelluistinserttime = 0.0;
    double averagellslistinserttime = 0.0;
    double averagebstreeinserttime = 0.0;

    double maxaulistinserttime = 0.0;
    double maxaslistinserttime = 0.0;
    double maxlluistinserttime = 0.0;
    double maxllslistinserttime = 0.0;
    double maxbstreeinserttime = 0.0;

    double minaulistinserttime = 1e9;
    double minaslistinserttime = 1e9;
    double minlluistinserttime = 1e9;
    double minllslistinserttime = 1e9;
    double minbstreeinserttime = 1e9;

    for (int i = 0; i < 500; ++i) {
        averageaulistinserttime += aulistinserttimes[i];
        averageaslistinserttime += aslistinserttimes[i];
        averagelluistinserttime += llulistinserttimes[i];
        averagellslistinserttime += llslistinserttimes[i];
        averagebstreeinserttime += bstreeinserttimes[i];

        if (aulistinserttimes[i] > maxaulistinserttime) {
            maxaulistinserttime = aulistinserttimes[i];
        }
        if (aslistinserttimes[i] > maxaslistinserttime) {
            maxaslistinserttime = aslistinserttimes[i];
        }
        if (llulistinserttimes[i] > maxlluistinserttime) {
            maxlluistinserttime = llulistinserttimes[i];
        }
        if (llslistinserttimes[i] > maxllslistinserttime) {
            maxllslistinserttime = llslistinserttimes[i];
        }
        if (bstreeinserttimes[i] > maxbstreeinserttime) {
            maxbstreeinserttime = bstreeinserttimes[i];
        }

        if (aulistinserttimes[i] < minaulistinserttime) {
            minaulistinserttime = aulistinserttimes[i];
        }
        if (aslistinserttimes[i] < minaslistinserttime) {
            minaslistinserttime = aslistinserttimes[i];
        }
        if (llulistinserttimes[i] < minlluistinserttime) {
            minlluistinserttime = llulistinserttimes[i];
        }
        if (llslistinserttimes[i] < minllslistinserttime) {
            minllslistinserttime = llslistinserttimes[i];
        }
        if (bstreeinserttimes[i] < minbstreeinserttime) {
            minbstreeinserttime = bstreeinserttimes[i];
        }
    }
    averageaulistinserttime /= 500.0;
    averageaslistinserttime /= 500.0;
    averagelluistinserttime /= 500.0;
    averagellslistinserttime /= 500.0;
    averagebstreeinserttime /= 500.0;

    // Store results in tableEntry struct
    entry->aulistinsert[0] = minaulistinserttime;
    entry->aulistinsert[1] = maxaulistinserttime;
    entry->aulistinsert[2] = averageaulistinserttime;
    
    entry->aslistinsert[0] = minaslistinserttime;
    entry->aslistinsert[1] = maxaslistinserttime;
    entry->aslistinsert[2] = averageaslistinserttime;
    
    entry->llulistinsert[0] = minlluistinserttime;
    entry->llulistinsert[1] = maxlluistinserttime;
    entry->llulistinsert[2] = averagelluistinserttime;
    
    entry->llslistinsert[0] = minllslistinserttime;
    entry->llslistinsert[1] = maxllslistinserttime;
    entry->llslistinsert[2] = averagellslistinserttime;
    
    entry->bstreeinsert[0] = minbstreeinserttime;
    entry->bstreeinsert[1] = maxbstreeinserttime;
    entry->bstreeinsert[2] = averagebstreeinserttime;
}

void SearchAnalysis(int array[], tableEntry* entry){
    AUList aulist;
    ASList aslist(500);
    LLUList lluist;
    LLSList llslist;
    TreeType bstree;

    double aulistsearchtimes[500];
    double aslistsearchtimes[500];
    double llulistsearchtimes[500];
    double llslistsearchtimes[500];
    double bstreesearchtimes[500];

    // First, populate all lists with the array data
    for (int i = 0; i < 500; ++i) {
        aulist.PutItem(array[i]);
        aslist.PutItem(array[i]);
        lluist.PutItem(array[i]);
        llslist.PutItem(array[i]);
        bstree.PutItem(array[i]);
    }

    // Now search for each item and time the operations
    for (int i = 0; i < 500; ++i) {
        aulistsearchtimes[i] = functionTimerSearch<AUList>(aulist, (AUList::GetItem), array[i]);
        aslistsearchtimes[i] = functionTimerSearch<ASList>(aslist, (ASList::GetItem), array[i]);
        llulistsearchtimes[i] = functionTimerSearch<LLUList>(lluist, (LLUList::GetItem), array[i]);
        llslistsearchtimes[i] = functionTimerSearch<LLSList>(llslist, (LLSList::GetItem), array[i]);
        bstreesearchtimes[i] = functionTimerSearch<TreeType>(bstree, (TreeType::GetItem), array[i]);
    }

    double averageaulistsearchtime = 0.0;
    double averageaslistsearchtime = 0.0;
    double averagelluistsearchtime = 0.0;
    double averagellssearchtime = 0.0;
    double averagebstreesearchtime = 0.0;

    double maxaulistsearchtime = 0.0;
    double maxaslistsearchtime = 0.0;
    double maxlluistsearchtime = 0.0;
    double maxllssearchtime = 0.0;
    double maxbstreesearchtime = 0.0;

    double minaulistsearchtime = 1e9;
    double minaslistsearchtime = 1e9;
    double minlluistsearchtime = 1e9;
    double minllssearchtime = 1e9;
    double minbstreesearchtime = 1e9;

    for (int i = 0; i < 500; ++i) {
        averageaulistsearchtime += aulistsearchtimes[i];
        averageaslistsearchtime += aslistsearchtimes[i];
        averagelluistsearchtime += llulistsearchtimes[i];
        averagellssearchtime += llslistsearchtimes[i];
        averagebstreesearchtime += bstreesearchtimes[i];

        if (aulistsearchtimes[i] > maxaulistsearchtime) {
            maxaulistsearchtime = aulistsearchtimes[i];
        }
        if (aslistsearchtimes[i] > maxaslistsearchtime) {
            maxaslistsearchtime = aslistsearchtimes[i];
        }
        if (llulistsearchtimes[i] > maxlluistsearchtime) {
            maxlluistsearchtime = llulistsearchtimes[i];
        }
        if (llslistsearchtimes[i] > maxllssearchtime) {
            maxllssearchtime = llslistsearchtimes[i];
        }
        if (bstreesearchtimes[i] > maxbstreesearchtime) {
            maxbstreesearchtime = bstreesearchtimes[i];
        }

        if (aulistsearchtimes[i] < minaulistsearchtime) {
            minaulistsearchtime = aulistsearchtimes[i];
        }
        if (aslistsearchtimes[i] < minaslistsearchtime) {
            minaslistsearchtime = aslistsearchtimes[i];
        }
        if (llulistsearchtimes[i] < minlluistsearchtime) {
            minlluistsearchtime = llulistsearchtimes[i];
        }
        if (llslistsearchtimes[i] < minllssearchtime) {
            minllssearchtime = llslistsearchtimes[i];
        }
        if (bstreesearchtimes[i] < minbstreesearchtime) {
            minbstreesearchtime = bstreesearchtimes[i];
        }
    }
    averageaulistsearchtime /= 500.0;
    averageaslistsearchtime /= 500.0;
    averagelluistsearchtime /= 500.0;
    averagellssearchtime /= 500.0;
    averagebstreesearchtime /= 500.0;

    // Store results in tableEntry struct
    entry->aulistsearch[0] = minaulistsearchtime;
    entry->aulistsearch[1] = maxaulistsearchtime;
    entry->aulistsearch[2] = averageaulistsearchtime;
    
    entry->aslistsearch[0] = minaslistsearchtime;
    entry->aslistsearch[1] = maxaslistsearchtime;
    entry->aslistsearch[2] = averageaslistsearchtime;
    
    entry->llulistsearch[0] = minlluistsearchtime;
    entry->llulistsearch[1] = maxlluistsearchtime;
    entry->llulistsearch[2] = averagelluistsearchtime;
    
    entry->llslistsearch[0] = minllssearchtime;
    entry->llslistsearch[1] = maxllssearchtime;
    entry->llslistsearch[2] = averagellssearchtime;
    
    entry->bstreesearch[0] = minbstreesearchtime;
    entry->bstreesearch[1] = maxbstreesearchtime;
    entry->bstreesearch[2] = averagebstreesearchtime;
}

void DeleteAnalysis(int array[], tableEntry* entry){
    AUList aulist;
    ASList aslist(500);
    LLUList lluist;
    LLSList llslist;
    TreeType bstree;

    double aulistdeletetimes[500];
    double aslistdeletetimes[500];
    double llulistdeletetimes[500];
    double llslistdeletetimes[500];
    double bstreedeletetimes[500];

    // First, populate all lists with the array data
    for (int i = 0; i < 500; ++i) {
        aulist.PutItem(array[i]);
        aslist.PutItem(array[i]);
        lluist.PutItem(array[i]);
        llslist.PutItem(array[i]);
        bstree.PutItem(array[i]);
    }

    // Create a shuffled copy of the array for random deletion order
    int *deleteOrder = new int[500];
    for (int i = 0; i < 500; ++i) {
        deleteOrder[i] = array[i];
    }
    // Fisher-Yates shuffle
    for (int i = 499; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = deleteOrder[i];
        deleteOrder[i] = deleteOrder[j];
        deleteOrder[j] = temp;
    }

    // Now delete each item in random order and time the operations
    for (int i = 0; i < 500; ++i) {
        aulistdeletetimes[i] = functionTimerinsert<AUList>(aulist, (AUList::DeleteItem), deleteOrder[i]);
        aslistdeletetimes[i] = functionTimerinsert<ASList>(aslist, (ASList::DeleteItem), deleteOrder[i]);
        llulistdeletetimes[i] = functionTimerinsert<LLUList>(lluist, (LLUList::DeleteItem), deleteOrder[i]);
        llslistdeletetimes[i] = functionTimerinsert<LLSList>(llslist, (LLSList::DeleteItem), deleteOrder[i]);
        bstreedeletetimes[i] = functionTimerinsert<TreeType>(bstree, (TreeType::DeleteItem), deleteOrder[i]);
    }

    double averageaulistdeletetime = 0.0;
    double averageaslistdeletetime = 0.0;
    double averagelluistdeletetime = 0.0;
    double averagellsdeletetime = 0.0;
    double averagebstreedeletetime = 0.0;

    double maxaulistdeletetime = 0.0;
    double maxaslistdeletetime = 0.0;
    double maxlluistdeletetime = 0.0;
    double maxllsdeletetime = 0.0;
    double maxbstreedeletetime = 0.0;

    double minaulistdeletetime = 1e9;
    double minaslistdeletetime = 1e9;
    double minlluistdeletetime = 1e9;
    double minllsdeletetime = 1e9;
    double minbstreedeletetime = 1e9;

    for (int i = 0; i < 500; ++i) {
        averageaulistdeletetime += aulistdeletetimes[i];
        averageaslistdeletetime += aslistdeletetimes[i];
        averagelluistdeletetime += llulistdeletetimes[i];
        averagellsdeletetime += llslistdeletetimes[i];
        averagebstreedeletetime += bstreedeletetimes[i];

        if (aulistdeletetimes[i] > maxaulistdeletetime) {
            maxaulistdeletetime = aulistdeletetimes[i];
        }
        if (aslistdeletetimes[i] > maxaslistdeletetime) {
            maxaslistdeletetime = aslistdeletetimes[i];
        }
        if (llulistdeletetimes[i] > maxlluistdeletetime) {
            maxlluistdeletetime = llulistdeletetimes[i];
        }
        if (llslistdeletetimes[i] > maxllsdeletetime) {
            maxllsdeletetime = llslistdeletetimes[i];
        }
        if (bstreedeletetimes[i] > maxbstreedeletetime) {
            maxbstreedeletetime = bstreedeletetimes[i];
        }

        if (aulistdeletetimes[i] < minaulistdeletetime) {
            minaulistdeletetime = aulistdeletetimes[i];
        }
        if (aslistdeletetimes[i] < minaslistdeletetime) {
            minaslistdeletetime = aslistdeletetimes[i];
        }
        if (llulistdeletetimes[i] < minlluistdeletetime) {
            minlluistdeletetime = llulistdeletetimes[i];
        }
        if (llslistdeletetimes[i] < minllsdeletetime) {
            minllsdeletetime = llslistdeletetimes[i];
        }
        if (bstreedeletetimes[i] < minbstreedeletetime) {
            minbstreedeletetime = bstreedeletetimes[i];
        }
    }
    averageaulistdeletetime /= 500.0;
    averageaslistdeletetime /= 500.0;
    averagelluistdeletetime /= 500.0;
    averagellsdeletetime /= 500.0;
    averagebstreedeletetime /= 500.0;

    // Store results in tableEntry struct
    entry->aulistdelete[0] = minaulistdeletetime;
    entry->aulistdelete[1] = maxaulistdeletetime;
    entry->aulistdelete[2] = averageaulistdeletetime;
    
    entry->aslistdelete[0] = minaslistdeletetime;
    entry->aslistdelete[1] = maxaslistdeletetime;
    entry->aslistdelete[2] = averageaslistdeletetime;
    
    entry->llulistdelete[0] = minlluistdeletetime;
    entry->llulistdelete[1] = maxlluistdeletetime;
    entry->llulistdelete[2] = averagelluistdeletetime;
    
    entry->llslistdelete[0] = minllsdeletetime;
    entry->llslistdelete[1] = maxllsdeletetime;
    entry->llslistdelete[2] = averagellsdeletetime;
    
    entry->bstreedelete[0] = minbstreedeletetime;
    entry->bstreedelete[1] = maxbstreedeletetime;
    entry->bstreedelete[2] = averagebstreedeletetime;
    
    delete[] deleteOrder;
}

void printTableResults() {
    cout << "\n=================================================" << endl;
    cout << "       PERFORMANCE ANALYSIS RESULTS (ns)" << endl;
    cout << "=================================================" << endl;

    cout << "\nFormat: Min / Max / Avg (nanoseconds)\n" << endl;

    // Print results for each entry
    for (int entry = 0; entry < 10; ++entry) {
        cout << "ENTRY " << (entry + 1) << ":" << endl;
        cout << "  Operation      | AUList               | ASList               | LLUList              | LLSList              | BSTree" << endl;
        cout << "  ===============|===============+======|======================|======================|======================|=====================" << endl;
        
        // INSERT row
        printf("  INSERT         | ");
        printf("%6.0f/%6.0f/%6.0f | ", results[entry].aulistinsert[0], results[entry].aulistinsert[1], results[entry].aulistinsert[2]);
        printf("%6.0f/%6.0f/%6.0f | ", results[entry].aslistinsert[0], results[entry].aslistinsert[1], results[entry].aslistinsert[2]);
        printf("%6.0f/%6.0f/%6.0f | ", results[entry].llulistinsert[0], results[entry].llulistinsert[1], results[entry].llulistinsert[2]);
        printf("%6.0f/%6.0f/%6.0f | ", results[entry].llslistinsert[0], results[entry].llslistinsert[1], results[entry].llslistinsert[2]);
        printf("%6.0f/%6.0f/%6.0f\n", results[entry].bstreeinsert[0], results[entry].bstreeinsert[1], results[entry].bstreeinsert[2]);
        
        // SEARCH row
        printf("  SEARCH         | ");
        printf("%6.0f/%6.0f/%6.0f | ", results[entry].aulistsearch[0], results[entry].aulistsearch[1], results[entry].aulistsearch[2]);
        printf("%6.0f/%6.0f/%6.0f | ", results[entry].aslistsearch[0], results[entry].aslistsearch[1], results[entry].aslistsearch[2]);
        printf("%6.0f/%6.0f/%6.0f | ", results[entry].llulistsearch[0], results[entry].llulistsearch[1], results[entry].llulistsearch[2]);
        printf("%6.0f/%6.0f/%6.0f | ", results[entry].llslistsearch[0], results[entry].llslistsearch[1], results[entry].llslistsearch[2]);
        printf("%6.0f/%6.0f/%6.0f\n", results[entry].bstreesearch[0], results[entry].bstreesearch[1], results[entry].bstreesearch[2]);
        
        // DELETE row
        printf("  DELETE         | ");
        printf("%6.0f/%6.0f/%6.0f | ", results[entry].aulistdelete[0], results[entry].aulistdelete[1], results[entry].aulistdelete[2]);
        printf("%6.0f/%6.0f/%6.0f | ", results[entry].aslistdelete[0], results[entry].aslistdelete[1], results[entry].aslistdelete[2]);
        printf("%6.0f/%6.0f/%6.0f | ", results[entry].llulistdelete[0], results[entry].llulistdelete[1], results[entry].llulistdelete[2]);
        printf("%6.0f/%6.0f/%6.0f | ", results[entry].llslistdelete[0], results[entry].llslistdelete[1], results[entry].llslistdelete[2]);
        printf("%6.0f/%6.0f/%6.0f\n", results[entry].bstreedelete[0], results[entry].bstreedelete[1], results[entry].bstreedelete[2]);
        
        cout << endl;
    }
    
    cout << "AVERAGE OF ENTRIES:" << endl;
    cout << "  Operation      | AUList               | ASList               | LLUList              | LLSList              | BSTree" << endl;
    cout << "  ===============|======================|======================|======================|======================|=====================" << endl;
    
    // Calculate averages for INSERT
    double avgAUlistinsert[3] = {0, 0, 0};
    double avgASlistinsert[3] = {0, 0, 0};
    double avgLLUlistinsert[3] = {0, 0, 0};
    double avgLLSlistinsert[3] = {0, 0, 0};
    double avgBstreeinsert[3] = {0, 0, 0};
    
    for (int i = 0; i < 10; ++i) {
        avgAUlistinsert[0] += results[i].aulistinsert[0];
        avgAUlistinsert[1] += results[i].aulistinsert[1];
        avgAUlistinsert[2] += results[i].aulistinsert[2];
        avgASlistinsert[0] += results[i].aslistinsert[0];
        avgASlistinsert[1] += results[i].aslistinsert[1];
        avgASlistinsert[2] += results[i].aslistinsert[2];
        avgLLUlistinsert[0] += results[i].llulistinsert[0];
        avgLLUlistinsert[1] += results[i].llulistinsert[1];
        avgLLUlistinsert[2] += results[i].llulistinsert[2];
        avgLLSlistinsert[0] += results[i].llslistinsert[0];
        avgLLSlistinsert[1] += results[i].llslistinsert[1];
        avgLLSlistinsert[2] += results[i].llslistinsert[2];
        avgBstreeinsert[0] += results[i].bstreeinsert[0];
        avgBstreeinsert[1] += results[i].bstreeinsert[1];
        avgBstreeinsert[2] += results[i].bstreeinsert[2];
    }
    for (int i = 0; i < 3; ++i) {
        avgAUlistinsert[i] /= 10.0;
        avgASlistinsert[i] /= 10.0;
        avgLLUlistinsert[i] /= 10.0;
        avgLLSlistinsert[i] /= 10.0;
        avgBstreeinsert[i] /= 10.0;
    }
    
    printf("  INSERT         | ");
    printf("%6ld/%6ld/%6ld | ", (long)round(avgAUlistinsert[0]), (long)round(avgAUlistinsert[1]), (long)round(avgAUlistinsert[2]));
    printf("%6ld/%6ld/%6ld | ", (long)round(avgASlistinsert[0]), (long)round(avgASlistinsert[1]), (long)round(avgASlistinsert[2]));
    printf("%6ld/%6ld/%6ld | ", (long)round(avgLLUlistinsert[0]), (long)round(avgLLUlistinsert[1]), (long)round(avgLLUlistinsert[2]));
    printf("%6ld/%6ld/%6ld | ", (long)round(avgLLSlistinsert[0]), (long)round(avgLLSlistinsert[1]), (long)round(avgLLSlistinsert[2]));
    printf("%6ld/%6ld/%6ld\n", (long)round(avgBstreeinsert[0]), (long)round(avgBstreeinsert[1]), (long)round(avgBstreeinsert[2]));
    
    // Calculate averages for SEARCH
    double avgAUlistsearch[3] = {0, 0, 0};
    double avgASlistsearch[3] = {0, 0, 0};
    double avgLLUlistsearch[3] = {0, 0, 0};
    double avgLLSlistsearch[3] = {0, 0, 0};
    double avgBstreesearch[3] = {0, 0, 0};
    
    for (int i = 0; i < 10; ++i) {
        avgAUlistsearch[0] += results[i].aulistsearch[0];
        avgAUlistsearch[1] += results[i].aulistsearch[1];
        avgAUlistsearch[2] += results[i].aulistsearch[2];
        avgASlistsearch[0] += results[i].aslistsearch[0];
        avgASlistsearch[1] += results[i].aslistsearch[1];
        avgASlistsearch[2] += results[i].aslistsearch[2];
        avgLLUlistsearch[0] += results[i].llulistsearch[0];
        avgLLUlistsearch[1] += results[i].llulistsearch[1];
        avgLLUlistsearch[2] += results[i].llulistsearch[2];
        avgLLSlistsearch[0] += results[i].llslistsearch[0];
        avgLLSlistsearch[1] += results[i].llslistsearch[1];
        avgLLSlistsearch[2] += results[i].llslistsearch[2];
    avgBstreesearch[0] += results[i].bstreesearch[0];
    avgBstreesearch[1] += results[i].bstreesearch[1];
    avgBstreesearch[2] += results[i].bstreesearch[2];
    }
    for (int i = 0; i < 3; ++i) {
        avgAUlistsearch[i] /= 10.0;
        avgASlistsearch[i] /= 10.0;
        avgLLUlistsearch[i] /= 10.0;
        avgLLSlistsearch[i] /= 10.0;
        avgBstreesearch[i] /= 10.0;
    }
    
    printf("  SEARCH         | ");
    printf("%6ld/%6ld/%6ld | ", (long)round(avgAUlistsearch[0]), (long)round(avgAUlistsearch[1]), (long)round(avgAUlistsearch[2]));
    printf("%6ld/%6ld/%6ld | ", (long)round(avgASlistsearch[0]), (long)round(avgASlistsearch[1]), (long)round(avgASlistsearch[2]));
    printf("%6ld/%6ld/%6ld | ", (long)round(avgLLUlistsearch[0]), (long)round(avgLLUlistsearch[1]), (long)round(avgLLUlistsearch[2]));
    printf("%6ld/%6ld/%6ld | ", (long)round(avgLLSlistsearch[0]), (long)round(avgLLSlistsearch[1]), (long)round(avgLLSlistsearch[2]));
    printf("%6ld/%6ld/%6ld\n", (long)round(avgBstreesearch[0]), (long)round(avgBstreesearch[1]), (long)round(avgBstreesearch[2]));
    
    // Calculate averages for DELETE
    double avgAUlistdelete[3] = {0, 0, 0};
    double avgASlistdelete[3] = {0, 0, 0};
    double avgLLUlistdelete[3] = {0, 0, 0};
    double avgLLSlistdelete[3] = {0, 0, 0};
    double avgBstreedelete[3] = {0, 0, 0};
    
    for (int i = 0; i < 10; ++i) {
        avgAUlistdelete[0] += results[i].aulistdelete[0];
        avgAUlistdelete[1] += results[i].aulistdelete[1];
        avgAUlistdelete[2] += results[i].aulistdelete[2];
        avgASlistdelete[0] += results[i].aslistdelete[0];
        avgASlistdelete[1] += results[i].aslistdelete[1];
        avgASlistdelete[2] += results[i].aslistdelete[2];
        avgLLUlistdelete[0] += results[i].llulistdelete[0];
        avgLLUlistdelete[1] += results[i].llulistdelete[1];
        avgLLUlistdelete[2] += results[i].llulistdelete[2];
        avgLLSlistdelete[0] += results[i].llslistdelete[0];
        avgLLSlistdelete[1] += results[i].llslistdelete[1];
        avgLLSlistdelete[2] += results[i].llslistdelete[2];
        avgBstreedelete[0] += results[i].bstreedelete[0];
        avgBstreedelete[1] += results[i].bstreedelete[1];
        avgBstreedelete[2] += results[i].bstreedelete[2];
    }
    for (int i = 0; i < 3; ++i) {
        avgAUlistdelete[i] /= 10.0;
        avgASlistdelete[i] /= 10.0;
        avgLLUlistdelete[i] /= 10.0;
        avgLLSlistdelete[i] /= 10.0;
        avgBstreedelete[i] /= 10.0;
    }
    
    printf("  DELETE         | ");
    printf("%6ld/%6ld/%6ld | ", (long)round(avgAUlistdelete[0]), (long)round(avgAUlistdelete[1]), (long)round(avgAUlistdelete[2]));
    printf("%6ld/%6ld/%6ld | ", (long)round(avgASlistdelete[0]), (long)round(avgASlistdelete[1]), (long)round(avgASlistdelete[2]));
    printf("%6ld/%6ld/%6ld | ", (long)round(avgLLUlistdelete[0]), (long)round(avgLLUlistdelete[1]), (long)round(avgLLUlistdelete[2]));
    printf("%6ld/%6ld/%6ld | ", (long)round(avgLLSlistdelete[0]), (long)round(avgLLSlistdelete[1]), (long)round(avgLLSlistdelete[2]));
    printf("%6ld/%6ld/%6ld\n", (long)round(avgBstreedelete[0]), (long)round(avgBstreedelete[1]), (long)round(avgBstreedelete[2]));



    cout << "=================================================" << endl;
    cout << "      Analysis Complete" << endl;
    cout << "=================================================" << endl;
}

int main() {
    for (int i = 0; i < 10; ++i) {
        cout << "Generating random array of length 500: ";
        int *list = arraygen();
        //cout << "\nArray generated. Beginning insertion analysis..." << endl;
        InsertAnalysis(list, &results[i]);
        cout << "\nInsertion analysis complete." << endl;
        //cout << "\nBeginning search analysis..." << endl;
        SearchAnalysis(list, &results[i]);
        cout << "Search analysis complete." << endl;
        //cout << "\nBeginning delete analysis..." << endl;
        DeleteAnalysis(list, &results[i]);
        cout << "Delete analysis complete.\n" << endl;
        delete[] list;
    }
    printTableResults();
    return 0;
}
