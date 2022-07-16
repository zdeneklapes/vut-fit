//
//  StockInfoView.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/28/22.
//

import Foundation
import SwiftUI
import SwiftYFinance

enum PriceToShow {
    case regMarketPrice
    case low52w
    case high52w
}

struct PriceView : View {
    @State var price : Float?
    let timer = Timer.publish(every: 5, on: .main, in: .common).autoconnect()
    let symbol: String
    let toShow : PriceToShow
    
    var body: some View {
        Text("\(price?.round(to: 2).description ?? "-") $")
            .onAppear { updatePrice() }
            .onReceive(timer) { input in updatePrice() }
    }
    
    func updatePrice() {
        SwiftYFinance.summaryDataBy(identifier: self.symbol) { data, error in
            if let error = error { print(error); return }
            
            //
            switch toShow {
            case .regMarketPrice:
                self.price = data?.price?.regularMarketPrice
            case .low52w:
                self.price = data?.summaryDetail?.fiftyTwoWeekLow
            case .high52w:
                self.price = data?.summaryDetail?.fiftyTwoWeekHigh
            }
        }
    }
}


struct WatchlistStockInfoView: View {
    @StateObject var stockInWatchlistViewModel : StockInWatchlistViewModel = StockInWatchlistViewModel()
    @State var stockInfo: StockInfoWatchlistCellModel
    let color = 0.9

    //
    struct StockAttributesView: View {
        let desc: String
        let symbol: String
        let toShow: PriceToShow

        //
        var body: some View {
            VStack {
                Text(desc).modifier(StockInfoAttributeDescModifier())
                PriceView(symbol: self.symbol, toShow: self.toShow).modifier(StockInfoAttributeValueModifier())
            }
        }
    }

    //
    var body: some View {
        NavigationLink(destination: StockDetailView(symbol: stockInfo.ticker).environmentObject(stockInWatchlistViewModel)) {
            HStack {
                HStack {
                    VStack {
                        Text(stockInfo.ticker).font(.subheadline).foregroundColor(.black)
                        Text(stockInfo.companyName).modifier(StockInfoAttributeDescModifier())
                    }
                    Spacer()
                    HStack {
                        StockAttributesView(desc: "52w Low", symbol: stockInfo.ticker, toShow: .low52w)
                        StockAttributesView(desc: "52w High", symbol: stockInfo.ticker, toShow: .high52w)
                    }
                    Spacer()
                    PriceView(symbol: stockInfo.ticker, toShow: .regMarketPrice)
                }
                Image(systemName: "chevron.right")
            }
            .padding(.all, 5)
        }
        .background(Color(red: color, green: color, blue: color))
        .cornerRadius(10)
        .padding(.horizontal, 5)
    }
}

struct StockInfoView_Previews: PreviewProvider {
    static var previews: some View {
        WatchlistStockInfoView(stockInfo: StockInfoWatchlistCellModel(id: "1",
                ticker: "AAPL",
                companyName: "Apple Inc.",
                low52w: "120.00$",
                high52w: "183.00$",
                price: "145.60$"))
    }
}
