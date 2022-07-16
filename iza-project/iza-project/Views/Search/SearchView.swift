//
//  SearchView.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/26/22.
//

import SwiftUI
import Foundation
import Combine
import SwiftYFinance

struct SearchView: View {
    @State var searchString: String = ""
    @State var foundContainer: [YFQuoteSearchResult] = []
    
    //
    var body: some View {
        NavigationView {
            VStack {
                HStack {
                    Image(systemName: "magnifyingglass")
                    TextField("Search", text: $searchString, onCommit: self.searchObjects)
                }.modifier(SearchViewTextfieldViewModifier())
                
                //
                if !self.foundContainer.isEmpty {
                    List {
                        ForEach(self.foundContainer, id: \.symbol) { result in
                            SearchResultListItemView(result: result).listRowInsets(EdgeInsets())
                        }
                    }
                } else {
                    Spacer()
                    Text("Type any Company name or Stock ticker to start searching")
                        .padding(.horizontal, 20)
                        .foregroundColor(.gray)
                        .multilineTextAlignment(.center)
                    Spacer()
                }
            }
            .navigationTitle("Search Company")
            .onAppear(perform: self.searchObjects)
        }
    }
    
    func searchObjects() {
        SwiftYFinance.fetchSearchDataBy(searchTerm: self.searchString) { data, error in
            if let _ = error { return }
            //
            self.foundContainer = data!
        }
    }
}

struct SearchView_Previews: PreviewProvider {
    static var previews: some View {
        SearchView()
    }
}

