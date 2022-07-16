//
//  File.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/31/22.
//

import Foundation
import SwiftUI

struct ActionWatchlist : View {
    @EnvironmentObject var tab : AppTabNavigationViewModel
    @Binding var activeSheet : SheetsWatchlistExpanded?
    
    var body: some View{
        HStack {
            Button("Add Symbol") {
                tab.selectedTab = .search
            }.modifier(TextEditModifier())
            Button("Edit Watchlist") {
                activeSheet = .sheet2
            }.modifier(TextEditModifier())
        } .padding(.vertical, 5)
    }
}
