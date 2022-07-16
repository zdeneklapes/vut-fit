//
//  WatchlistView.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/26/22.
//

import SwiftUI

struct WatchlistView: View {
    //
    @StateObject var watchlistViewModel = WatchlistViewModel()
    @State private var selectedCells: Set<WatchlistModel> = []

    //
    var body: some View {
        NavigationView {
            ExpandableListView {
                ForEach(watchlistViewModel.list) { watchlist in
                    ExpandableListContentView(title: watchlist.name, isExpanded: self.selectedCells.contains(watchlist)) {
                        WatchlistExpandedView(watchlistModel: watchlist)
                    }
                    .modifier(ScrollCell())
                    .onTapGesture { self.tapGesture(watchlist: watchlist) }
                }
            }
            .navigationTitle("Watchlists")
            .toolbar {
                HStack {
                    NavigationLink(destination: CreateWatchlistView()) {
                        Image(systemName: "plus")
                    }
                    .padding(.horizontal, 10)
                }
            }
        }
        .environmentObject(watchlistViewModel)
        .onAppear { watchlistViewModel.getData() }
    }
}

extension WatchlistView {
    func tapGesture(watchlist: WatchlistModel) {
        if self.selectedCells.contains(watchlist) {
            self.selectedCells.remove(watchlist)
        } else {
            self.selectedCells.insert(watchlist)
        }
    }
}


