//
//  StockInWatchlistViewModel.swift
//  iza-project
//
//  Created by Zdeněk Lapeš on 5/28/22.
//

import Foundation
import Firebase
import SwiftYFinance

/// Handle CRUD Operations on DB table "StockInWatchlist"
class StockInWatchlistViewModel: ObservableObject {
    @Published var list: [StockInWatchlistModel] = []
    @Published var listStockInfoModel: [StockInfoWatchlistCellModel] = []

    //
    var watchlistModel: WatchlistModel = WatchlistModel(id: "", name: "")
    static var collectionName = "stock_in_watchlist"

    //
    init(watchlistModel: WatchlistModel) {
        self.watchlistModel = watchlistModel
        getDataForWatchlist()
    }
    
    init() { getDataAll() }
}

/// Extension implementing StockInWatchlistViewModel's functions
extension StockInWatchlistViewModel {
    func stockInWatchlistDocument(symbol: String) -> Array<StockInWatchlistModel>? {
        return list.filter{$0.ticker == symbol}
    }
    
    /// Check if symbol already in watchlist
    /// - Returns: Bool value if is in already
    func isInWatchlistAlready(symbol: String) -> Bool {
        return list.filter{$0.ticker == symbol}.count > 0
    }
    
    /// Get data with reference on watchlistModel property
    func getDataAll() {
        self.list.removeAll()
        Firestore.firestore().collection(StockInWatchlistViewModel.collectionName).getDocuments { snapshot, error in
            if let error = error { print(error); return }

            if let snapshot = snapshot {
                self.list = snapshot.documents.map { doc in
                    return StockInWatchlistModel(id: doc.documentID,
                                                 ticker: doc["ticker"] as? String ?? "",
                                                 watchlistID: (doc["watchlistID"] as? DocumentReference ?? nil)?.documentID ?? "")
                }
                
                // update StockInfoList
                self.fillListStockInfo()
            }
        }
    }

    /// Get all data in collection
    func getDataForWatchlist() {
        Firestore.firestore().collection(StockInWatchlistViewModel.collectionName).getDocuments { snapshot, error in
            if let error = error { print(error); return }

            if let snapshot = snapshot {
                //
                self.list.removeAll()
                
                //
                self.list = snapshot.documents.filter { doc in
                    let id: String = (doc["watchlistID"] as? DocumentReference ?? nil)? .documentID ?? ""
                    return id == self.watchlistModel.id
                } .map { doc in
                    return StockInWatchlistModel(
                        id: doc.documentID,
                        ticker: doc["ticker"] as? String ?? "",
                        watchlistID: (doc["watchlistID"] as? DocumentReference ?? nil)?.documentID ?? ""
                    )
                }
                
                // update StockInfoList
                self.fillListStockInfo()
            }
        }
    }

    /// Create record
    func addData(ticker: String) {
        let db = Firestore.firestore()
        let documentRefString = db.collection(WatchlistViewModel.collectionName).document(self.watchlistModel.id)
        let docRef = db.document(documentRefString.path)
        
        db.collection(StockInWatchlistViewModel.collectionName)
            .addDocument(data: ["ticker": ticker, "watchlistID": docRef]) { error in
                if let error = error { print(error); return }
                self.sendUpdateToObservers()
            }
    }
    
    /// Delete record
    func deleteData(stockInWatchlistModel: StockInWatchlistModel) {
        let _ = Firestore.firestore().collection(StockInWatchlistViewModel.collectionName).document(stockInWatchlistModel.id).delete { error in
            if let error = error { print(error); return }
            self.sendUpdateToObservers()
        }
    }
    
    // Specify the decimal place to round to using an enum
    // https://www.advancedswift.com/rounding-floats-and-doubles-in-swift/
    public enum RoundingPrecision {
        case ones
        case tenths
        case hundredths
    }

    // Round to the specific decimal place
    // https://www.advancedswift.com/rounding-floats-and-doubles-in-swift/
    public func preciseRound( _ value: Float, precision: RoundingPrecision = .ones) -> Float {
        switch precision {
        case .ones:
            return round(value)
        case .tenths:
            return round(value * 10) / 10.0
        case .hundredths:
            return round(value * 100) / 100.0
        }
    }
    
    //
    func fillListStockInfo() {
        //
        self.listStockInfoModel.removeAll()

        //
        for stock in self.list {
            SwiftYFinance.summaryDataBy(identifier: stock.ticker) { data, error in
                // handle errors
                if let error = error { print(error); return }
                guard let data = data else { return }

                // set stock info need for view
                let newStock = StockInfoWatchlistCellModel(
                    id: stock.id,
                    ticker: stock.ticker,
                    companyName: data.quoteType?.longName ?? "-",
                    low52w: data.summaryDetail?.fiftyTwoWeekLow?.round(to: 2).description ?? "-",
                    high52w: data.summaryDetail?.fiftyTwoWeekHigh?.round(to: 2).description ?? "-",
                    price: data.price?.regularMarketPrice?.round(to: 2).description ?? "-")
                

                if self.listStockInfoModel.contains(newStock) {
                    return
                } else {
                    DispatchQueue.main.async {
                        self.listStockInfoModel.append(newStock)
                    }
                }
            }
        }
    }
    
    func sendUpdateToObservers() {
        self.list.removeAll()
        self.getDataForWatchlist()
    }
}

// https://stackoverflow.com/a/54347186/14471542
extension Float {
    func round(to places: Int) -> Float {
        let divisor = pow(10.0, Float(places))
        return (self * divisor).rounded() / divisor
    }
}

