//
//  ff.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/29/22.
//

import SwiftUI
import SwiftYFinance

enum SheetsSearchView : Identifiable{
    var id: Int{self.hashValue}
    case favourite
}


struct SearchResultListItemView: View {
    @StateObject var stockInWatchlistViewModel : StockInWatchlistViewModel = StockInWatchlistViewModel()
    @State var activeSheet : SheetsSearchView?
    let result: YFQuoteSearchResult?
    
    //
    var body: some View {
        NavigationLink(destination: {
            StockDetailView(symbol: result?.symbol ?? "")
        }, label: {
            SearchStockInfoView(result: self.result)
            FavoriteIcon(activeSheet: $activeSheet, symbol: result?.symbol ?? "").environmentObject(stockInWatchlistViewModel)
        })
        .modifier(SearchStockResultViewModifier())
        .sheet(item: $activeSheet, onDismiss: {stockInWatchlistViewModel.getDataAll()}) { item in
            switch item {
            case .favourite:
                AddToWatchlist(symbol: result?.symbol ?? "")
            }
        }
    }
}


struct ListUnoView_Previews: PreviewProvider {
    static var previews: some View {
        SearchResultListItemView(result: nil)
    }
}
