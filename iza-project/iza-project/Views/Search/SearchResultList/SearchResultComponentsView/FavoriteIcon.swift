//
//  Fav.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/30/22.
//

import Foundation
import SwiftUI

struct FavoriteIcon: View {
    @EnvironmentObject var stockInWatchlistViewModel : StockInWatchlistViewModel
    @Binding var activeSheet : SheetsSearchView?
    var symbol : String
    
    //
    var body: some View {
        Button(action: {
            self.activeSheet = .favourite
        }, label: {
            Image(systemName: stockInWatchlistViewModel.isInWatchlistAlready(symbol: symbol) ? "star.fill" : "star")
                .foregroundColor(.yellow)
        })
    }
}


struct FavoriteIcon_Previews: PreviewProvider {
    static var previews: some View {
        FavoriteIcon(activeSheet: .constant(nil), symbol: "AAPL")
    }
}
