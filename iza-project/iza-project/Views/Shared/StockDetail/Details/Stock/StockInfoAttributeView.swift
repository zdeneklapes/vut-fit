//
//  StockInfoAttributeView.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/27/22.
//

import Foundation
import SwiftUI

struct StockInfoAttributeView: View {
    var desc: String
    var value: String
    var body: some View {
        HStack {
            Text(desc).modifier(StockInfoAttributeDescModifier())
            Spacer()
            Text(value).modifier(StockInfoAttributeValueModifier())
        }.padding(.horizontal)
    }
}
