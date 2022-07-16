//
//  dd.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/28/22.
//

import Foundation

struct StockInfoWatchlistCellModel: Identifiable, Hashable {
    let id: String
    let ticker: String
    var companyName: String
    var low52w: String
    var high52w: String
    var price: String

    init(id: String, ticker: String, companyName: String, low52w: String, high52w: String, price: String) {
        self.id = id
        self.ticker = ticker
        self.companyName = companyName
        self.low52w = low52w
        self.high52w = high52w
        self.price = price
    }
}

