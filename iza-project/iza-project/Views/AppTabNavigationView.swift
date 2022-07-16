//
//  ContentView.swift
//  Shared
//
//  Created by Zdeněk Lapeš on 4/15/22.
//

import SwiftUI
import SwiftYFinance

enum Tab {
    case home
    case portfolio
    case search
    case watchlist
    case menu
}

class AppTabNavigationViewModel: ObservableObject {
    @Published var selectedTab : Tab
    init(tab: Tab) {
        selectedTab = tab
    }
}

struct AppTabNavigationView: View {
    @StateObject var selected = AppTabNavigationViewModel(tab: .search)
    
    var body: some View {
        TabView(selection: $selected.selectedTab) {
            SearchView().modifier(TabItem(name: "Search", icon: "magnifyingglass", tagNum: Tab.search))
            WatchlistView().modifier(TabItem(name: "Watchlist", icon: "list.star", tagNum: Tab.watchlist))
        }.environmentObject(selected)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        AppTabNavigationView()
    }
}
