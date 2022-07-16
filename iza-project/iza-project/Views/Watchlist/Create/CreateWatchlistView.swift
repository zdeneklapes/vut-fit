//
//  WatchlistCreateView.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/28/22.
//

import Foundation
import SwiftUI

struct CreateWatchlistView: View {
    @EnvironmentObject var watchlistModel: WatchlistViewModel
    @Environment(\.presentationMode) var pm // take me back
    @State var watchlistName = ""
    
    //
    var body: some View {
        Form {
            Section("Info") {
                //
                TextField("Watchlist Name", text: $watchlistName)
                
                //
                HStack {
                    Button(action: {
                        watchlistModel.addData(name: watchlistName) // save to db
                        pm.wrappedValue.dismiss() // take me back
                    }, label: {
                        HStack { // spread the button width
                            Spacer()
                            Text("Create")
                            Spacer()
                        }
                        .foregroundColor(.white)
                        .padding(10)
                        .background(Color.accentColor)
                        .cornerRadius(8)
                    }).disabled(watchlistName == "")
                }
            }
        }
    }
}
