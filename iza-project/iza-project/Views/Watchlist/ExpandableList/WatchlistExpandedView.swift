//
//  WatchlistCellView.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/28/22.
//

import Foundation
import SwiftUI
import SwiftYFinance

enum SheetsWatchlistExpanded: Identifiable {
    var id: Int { self.hashValue }
    case sheet2
}


struct WatchlistExpandedView: View {
    @ObservedObject var stockInWatchlistViewModel: StockInWatchlistViewModel // must be ObservedObject, otherwise problem
    @EnvironmentObject var tab : AppTabNavigationViewModel
    @State var activeSheet : SheetsWatchlistExpanded?
    let watchlistModel: WatchlistModel
    
    //
    init(watchlistModel: WatchlistModel) {
        self.watchlistModel = watchlistModel
        stockInWatchlistViewModel = StockInWatchlistViewModel(watchlistModel: watchlistModel)
    }
    
    //
    var body: some View {
        VStack {
            ActionWatchlist(activeSheet: $activeSheet)
            
            // Show stocks inside watchlist if there are any
            if stockInWatchlistViewModel.listStockInfoModel != [] {
                ForEach(stockInWatchlistViewModel.listStockInfoModel) { stockDetail in
                    WatchlistStockInfoView(stockInfo: stockDetail)
                }
            } else {
                Text("Watchlist is empty")
            }
        }
        .sheet(item: $activeSheet) { item in
            switch item { case .sheet2: EditWatchlistView(watchlistModel: watchlistModel) }
        }
    }
}
