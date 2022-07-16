//
//  WatchlistViewModel.swift
//  iza-project
//
//  Created by Zdeněk Lapeš on 5/28/22.
//

import Foundation
import Firebase

/// Handle CRUD operation on WatchlistModel in Firebase DB
class WatchlistViewModel: ObservableObject {
    //
    @Published var list: [WatchlistModel] = []
    //
    static var collectionName = "watchlist"
    
    //
    init() { getData() }
    
    /// Set list property to retrieved data from DB
    func getData() {
        Firestore.firestore().collection(WatchlistViewModel.collectionName).getDocuments { snapshot, error in
            if let error = error { print("GET", error); return }
            
            // handle getRequest
            DispatchQueue.main.async {
                if let snapshot = snapshot {
                    self.list = snapshot.documents.map { doc in
                        return WatchlistModel(id: doc.documentID,
                                name: doc["name"] as? String ?? "")
                    }
                }
            }
        }
    }

    /// Create record in DB
    func addData(name: String) {
        Firestore.firestore().collection(WatchlistViewModel.collectionName).addDocument(data: ["name": name]) { error in
            if let error = error { print("CREATE", error); return }

            // update data
            self.getData()
        }
    }

    /// Delete record in DB
    /// - Parameter watchlistModel: contain information about deleted record
    func deleteData(watchlistModel: WatchlistModel) {
        let stockInWatchlistViewModel = StockInWatchlistViewModel(watchlistModel: watchlistModel)
        Firestore.firestore().collection(WatchlistViewModel.collectionName).document(watchlistModel.id).delete() { error in
            if let error = error { print("DELETE", error); return }
            
            // On delete cascade all stocks in this watchlist
            for item in stockInWatchlistViewModel.list {
                stockInWatchlistViewModel.deleteData(stockInWatchlistModel: item)
            }

            // Update List
            self.list.removeAll()
            self.getData()
        }
    }

    /// Update DB record
    /// - Parameter watchlistModel: contain information about updated record
    func updateData(watchlistM: WatchlistModel, newName: String) {
        Firestore.firestore()
            .collection(WatchlistViewModel.collectionName)
            .document(watchlistM.id)
            .setData(["name": newName], merge: true)
        self.getData()
    }
}
