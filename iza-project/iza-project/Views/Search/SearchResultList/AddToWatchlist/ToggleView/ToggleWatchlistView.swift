//
//  d.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/30/22.
//

import Foundation
import SwiftUI

struct ToggleWatchlistView : View {
    @StateObject var stockInWatchlistViewModel : StockInWatchlistViewModel
    @State var isInWatchlist: Bool = false
    
    //
    let watchlistModel: WatchlistModel
    let symbol: String
    
    //
    init(watchlistModel: WatchlistModel, symbol: String) {
        self.watchlistModel = watchlistModel
        self.symbol = symbol
        _stockInWatchlistViewModel = StateObject(wrappedValue: StockInWatchlistViewModel(watchlistModel: watchlistModel))
    }
    
    //
    var body: some View {
        Button(action: {}, label: {
            HStack {
                Text(watchlistModel.name)
                Spacer()
                Button(action: {
                    self.handleClick()
                }, label: {
                    Image(systemName: stockInWatchlistViewModel.isInWatchlistAlready(symbol: symbol) ? "star.fill" : "star")
                }).foregroundColor(.yellow)
            }
        })
    }
    
    /// Remove or create new record in Database based on change type (toggle on/off)
    func handleClick() {
        if stockInWatchlistViewModel.isInWatchlistAlready(symbol: symbol) {
            stockInWatchlistViewModel.deleteData(
                stockInWatchlistModel: stockInWatchlistViewModel.stockInWatchlistDocument(symbol: symbol)!.first(where: {_ in true})!
            )
        } else {
            stockInWatchlistViewModel.addData(ticker: symbol)
        }
    }
}
