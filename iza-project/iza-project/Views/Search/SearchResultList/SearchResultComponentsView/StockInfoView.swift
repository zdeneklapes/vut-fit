//
//  f.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/31/22.
//

import SwiftYFinance
import SwiftUI

struct SearchStockInfoView: View {
    let result: YFQuoteSearchResult?
    
    //
    var body: some View {
        HStack(alignment: .center, spacing: 0) {
            VStack(alignment: .leading) {
                Text(result?.symbol ?? "Not symbol").font(.title3).fontWeight(.bold)
                Text("\(result?.longname ?? "-")")
            }
            Spacer()
            Text("\(result?.assetType ?? "-")")
        }
    }
}



