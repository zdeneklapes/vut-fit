//
//  StockData.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/27/22.
//

import Foundation
import SwiftYFinance

struct StockData: Identifiable, Hashable {
    let id = UUID()
    let title: String
    let details: [Detail]
}

struct StockInfo {
    let title: String
    let data: [Detail]
}

struct Detail: Identifiable, Hashable {
    let id = UUID()
    let desc: String
    var value: String
    
    init(desc: String, value: Float) {
        print("float")
        self.desc = desc
        self.value = value.round(to: 2).description
    }
    
    init(desc: String, value: String) {
        print("string")
        self.desc = desc
        if value.isNumber() {
            self.value = String(format: "%.2f", Double(value) ?? "")
        } else {
            self.value = value
        }
    }
    
    init(desc: String, value: Int) {
        print("int")
        self.desc = desc
        self.value = value.description
    }
}

// https://stackoverflow.com/a/63147012/14471542
public extension String {
    func isNumber() -> Bool {
        let numberFormatter = NumberFormatter()
        return numberFormatter.number(from: self) != nil
    }
}

struct StockSearchModel {
    //
    static func data(identifierSummary: IdentifierSummary?) -> [StockData] {
        return [
            StockData(title: "Recommendation Trend", details: StockDetailData.recommendationTrend(identifierSummary: identifierSummary)),
            StockData(title: "Summary Detail", details: StockDetailData.summaryDetail(identifierSummary: identifierSummary)),
            StockData(title: "Price", details: StockDetailData.price(identifierSummary: identifierSummary)),
            StockData(title: "Quote type", details: StockDetailData.quoteType(identifierSummary: identifierSummary)),
            StockData(title: "Summary Profile", details: StockDetailData.summaryProfile(identifierSummary: identifierSummary)),
        ]
    }
}

struct StockDetailData {
    //
    static func recommendationTrend(identifierSummary: IdentifierSummary?) -> [Detail] {
        guard let _identifierSummary = identifierSummary else {
            return []
        }
        return [
            Detail(desc: "Strong Buy", value: getStringValue(_identifierSummary.recommendationTrend?.strongBuy)),
            Detail(desc: "Strong Sell", value: getStringValue(_identifierSummary.recommendationTrend?.strongSell)),
            Detail(desc: "Buy", value: getStringValue(_identifierSummary.recommendationTrend?.buy)),
            Detail(desc: "Hold", value: getStringValue(_identifierSummary.recommendationTrend?.hold)),
            Detail(desc: "Sell", value: getStringValue(_identifierSummary.recommendationTrend?.sell)),
        ]
    }

    //
    static func summaryDetail(identifierSummary: IdentifierSummary?) -> [Detail] {
        guard let _identifierSummary = identifierSummary else {
            return []
        }
        return [
            Detail(desc: "Trailing PE", value: getStringValue(_identifierSummary.summaryDetail?.trailingPE)),
            Detail(desc: "Forward PE", value: getStringValue(_identifierSummary.summaryDetail?.forwardPE)),
            Detail(desc: "Dividend Rate", value: getStringValue(_identifierSummary.summaryDetail?.dividendRate)),
            Detail(desc: "Dividend Yield", value: getStringValue(_identifierSummary.summaryDetail?.dividendYield)),
            Detail(desc: "52w Low", value: getStringValue(_identifierSummary.summaryDetail?.fiftyTwoWeekLow)),
            Detail(desc: "52w High", value: getStringValue(_identifierSummary.summaryDetail?.fiftyTwoWeekHigh)),
            Detail(desc: "Average Volume", value: getStringValue(_identifierSummary.summaryDetail?.averageVolume)),
            Detail(desc: "Previous Close", value: getStringValue(_identifierSummary.summaryDetail?.previousClose)),
        ]
    }

    //
    static func summaryProfile(identifierSummary: IdentifierSummary?) -> [Detail] {
        guard let _identifierSummary = identifierSummary else {
            return []
        }
        return [
            Detail(desc: "Country", value: getStringValue(_identifierSummary.summaryProfile?.country)),
            Detail(desc: "City", value: getStringValue(_identifierSummary.summaryProfile?.city)),
            Detail(desc: "Industry", value: getStringValue(_identifierSummary.summaryProfile?.industry)),
            Detail(desc: "Adress", value: getStringValue(_identifierSummary.summaryProfile?.address1)),
            Detail(desc: "FullT. Emps.", value: getStringValue(_identifierSummary.summaryProfile?.fullTimeEmployees)),
            Detail(desc: "Website", value: getStringValue(_identifierSummary.summaryProfile?.website)),
            Detail(desc: "Phone", value: getStringValue(_identifierSummary.summaryProfile?.phone)),
            Detail(desc: "Sector", value: getStringValue(_identifierSummary.summaryProfile?.sector)),
            Detail(desc: "Long Bus. Sum.", value: getStringValue(_identifierSummary.summaryProfile?.longBusinessSummary)),
        ]
    }

    //
    static func quoteType(identifierSummary: IdentifierSummary?) -> [Detail] {
        guard let _identifierSummary = identifierSummary else {
            return []
        }
        return [
            Detail(desc: "Exchange", value: getStringValue(_identifierSummary.quoteType?.exchange)),
            Detail(desc: "Quote Type", value: getStringValue(_identifierSummary.quoteType?.quoteType)),
            Detail(desc: "Symbol", value: getStringValue(_identifierSummary.quoteType?.symbol)),
            Detail(desc: "Underlying Symbol", value: getStringValue(_identifierSummary.quoteType?.underlyingSymbol)),
            Detail(desc: "Short Name", value: getStringValue(_identifierSummary.quoteType?.shortName)),
            Detail(desc: "Long Name", value: getStringValue(_identifierSummary.quoteType?.longName)),
            Detail(desc: "First Trade Date", value: getStringValue(_identifierSummary.quoteType?.firstTradeDateEpochUtc)),
            Detail(desc: "TimeZone", value: getStringValue(_identifierSummary.quoteType?.timeZoneShortName)),
            Detail(desc: "UUID", value: getStringValue(_identifierSummary.quoteType?.uuid)),
        ]
    }

    //
    static func price(identifierSummary: IdentifierSummary?) -> [Detail] {
        guard let _identifierSummary = identifierSummary else {
            return []
        }
        return [
            Detail(desc: "Reg Market Price", value: getStringValue(_identifierSummary.price?.regularMarketPrice)),
            Detail(desc: "Pre Market Time", value: getStringValue(_identifierSummary.price?.preMarketTime)),
            Detail(desc: "Exchange Name", value: getStringValue(_identifierSummary.price?.exchangeName)),
            Detail(desc: "Pre Market %", value: getStringValue(_identifierSummary.price?.preMarketChangePercent)),
            Detail(desc: "Currency Symbol", value: getStringValue(_identifierSummary.price?.currencySymbol)),
            Detail(desc: "Source", value: getStringValue(_identifierSummary.price?.regularMarketSource)),
            Detail(desc: "Delay", value: getStringValue(_identifierSummary.price?.exchangeDataDelayedBy)),
            Detail(desc: "Market Cap", value: getStringValue(_identifierSummary.price?.marketCap)),
            Detail(desc: "Max Age", value: getStringValue(_identifierSummary.price?.maxAge)),
            Detail(desc: "Currency", value: getStringValue(_identifierSummary.price?.currency)),
        ]
    }
}

func getStringValue(_ value: Any?) -> String {
    if value == nil {
        return "-"
    } else {
        if let x = value as? Int {
            return String(x)
        } else if let x = value as? Float {
            return String(x)
        } else if let x = value as? String {
            return x
        }
        return "-"
    }
}
