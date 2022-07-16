//
//  AddToWatchlists.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/30/22.
//

import Foundation
import SwiftUI

extension Binding {
    func didSet(execute: @escaping (Value) -> Void) -> Binding {
        return Binding(
            get: { self.wrappedValue },
            set: {
                self.wrappedValue = $0
                execute($0)
            }
        )
    }
}


struct AddToWatchlist : View {
    @StateObject var watchlistViewModel : WatchlistViewModel = WatchlistViewModel()
    @Environment(\.presentationMode) var pm // take me back
    let symbol: String
    
    //
    var body: some View {
        VStack {
            HStack {
                Spacer()
                Button(action: {
                    pm.wrappedValue.dismiss()
                }, label: {Text("Done").foregroundColor(.blue)})
            }.padding(.all)
            Text("Add to Watchlists:").font(.title2)
            Text("\(symbol)").font(.title2).fontWeight(.semibold)
            List {
                ForEach(watchlistViewModel.list) { watchlistModel in
                    ToggleWatchlistView(watchlistModel: watchlistModel, symbol: self.symbol)
                }
            }
        }.foregroundColor(Color.black)
    }
}

struct AddToWatchlist_Previews : PreviewProvider {
    static var previews: some View {
        AddToWatchlist(symbol: "AAPL")
    }
}
