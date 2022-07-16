//
//  EditWatchlistView.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/29/22.
//

import Foundation
import SwiftUI

struct EditWatchlistView: View {
    @State var watchlistName: String = ""
    @EnvironmentObject var watchlistViewModel: WatchlistViewModel
    @Environment(\.presentationMode) var pm // take me back
    var watchlistModel: WatchlistModel
    
    //
    init(watchlistModel: WatchlistModel) {
        self.watchlistModel = watchlistModel
//        self.watchlistName = watchlistModel.name
    }

    //
    var body: some View {
        VStack {
            HStack {
                Button(action: {
                    pm.wrappedValue.dismiss() // take me back
                }, label: {
                    Text("Cancel")
                })
                Spacer()
                Button(action: {
                    watchlistViewModel.updateData(watchlistM: self.watchlistModel, newName: watchlistName) // save to db
                    pm.wrappedValue.dismiss() // take me back
                }, label: {
                    Text("Update")
                }).disabled(watchlistName == "")
            }.padding(20)
            Text("Edit Watchlist").font(.title2)
            Text(watchlistModel.name).font(.title2).fontWeight(.bold)
            Form {
                Section(header: Text("New Name")) {
                    TextField(watchlistName, text: $watchlistName)
                }
                Section {
                    Button(action: {
                        watchlistViewModel.deleteData(watchlistModel: watchlistModel) // save to db
                        pm.wrappedValue.dismiss() // take me back
                    }, label: {
                        Text("Delete")
                            .foregroundColor(.red)
                            .frame(minWidth: 0, maxWidth: .infinity, minHeight: 0, maxHeight: .infinity, alignment: .center)
                    })
                }
            }
        }.ignoresSafeArea()
    }
}

struct EditWatchlistView_Previews: PreviewProvider {
    static var previews: some View {
        EditWatchlistView(watchlistModel: WatchlistModel(id: "1",name: "s"))
    }
}
