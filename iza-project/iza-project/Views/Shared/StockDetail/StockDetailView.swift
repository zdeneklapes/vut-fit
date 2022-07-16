//
//  StockView.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/26/22.
//

import SwiftUI
import SwiftYFinance



struct StockSearchedDetailHeaderView : View {
    let symbol: String
    @Binding var activeSheet: SheetsSearchView?
    
    var body: some View {
        HStack {
            Text("\(symbol)")
                .font(.title)
                .fontWeight(.bold)
            PriceView(symbol: symbol, toShow: .regMarketPrice)
                .font(.title2)
                .foregroundColor(.blue)
            Spacer()
            FavoriteIcon(activeSheet: $activeSheet, symbol: symbol)
        }
        .buttonStyle(.bordered)
        .padding(.horizontal)
    }
}

/// 
struct StockDetailView: View {
    @StateObject var stockInWatchlistViewModel : StockInWatchlistViewModel = StockInWatchlistViewModel()
    @State var identifierSummary: IdentifierSummary?
    @State private var selectedCells: Set<StockData> = []
    @State var details: [StockData]?
    @State var activeSheet : SheetsSearchView?
    let symbol: String
    
    //
    var body: some View {
        if details != nil {
            ScrollView {
                StockSearchedDetailHeaderView(symbol: symbol, activeSheet: $activeSheet).environmentObject(stockInWatchlistViewModel)
                StockGraphView(symbol: symbol)
                ExpandableListView {
                    ForEach(details!) { stockData in
                        ExpandableListContentView(title: stockData.title, isExpanded: self.selectedCells.contains(stockData)) {
                            ExpandInfoSearchedStockView(details: stockData.details)
                        }
                        .modifier(ScrollCell())
                        .onTapGesture {
                            if self.selectedCells.contains(stockData) {
                                self.selectedCells.remove(stockData)
                            } else {
                                self.selectedCells.insert(stockData)
                            }
                        }
                    }
                }
            }
            .foregroundColor(.black)
            .sheet(item: $activeSheet, onDismiss: {stockInWatchlistViewModel.getDataAll()}) { item in
                switch item { case .favourite: AddToWatchlist(symbol: symbol) }
            }
        } else {
            Text("No Data")
                .onAppear() {
                    SwiftYFinance.summaryDataBy(identifier: symbol) { data, error in
                        if let error = error { print(error); return }
                        self.details = StockSearchModel.data(identifierSummary: data!)
                    }
                }
        }
    }
}
