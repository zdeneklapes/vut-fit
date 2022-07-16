//
//  ExpandabelList.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/27/22.
//

import SwiftUI

struct ExpandableListView<Content: View>: View {
    @ViewBuilder let content: Content

    //
    var body: some View {
        VStack {
            Group {
                ScrollView {
                    content
                }
                        .frame(maxWidth: .infinity)
                        .padding(.top, 10)
            }
        }
    }
}
