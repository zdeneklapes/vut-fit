//
//  ExpandInfoSearchedStockView.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/29/22.
//

import Foundation
import SwiftUI

struct ExpandInfoSearchedStockView: View {
    var details: [Detail]
    let halfArray: Int

    //
    init(details: [Detail]) {
        self.details = details
        halfArray = details.count / 2
    }

    //
    var body: some View {
        HStack {
            // 1st half
            VStack {
                ForEach(details[0..<halfArray]) { detail in
                    StockInfoAttributeView(desc: detail.desc, value: detail.value)
                }
            }

            Divider()

            // 2nd half
            VStack {
                ForEach(details[halfArray..<details.count]) { detail in
                    StockInfoAttributeView(desc: detail.desc, value: detail.value)
                }
            }
        }
    }
}
