//
//  ExpandAbleLi.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/29/22.
//

import SwiftUI

struct ExpandableListContentView<Content: View>: View {
    //
    let title: String
    let isExpanded: Bool

    //
    @ViewBuilder let content: Content

    init(title: String, isExpanded: Bool, content: () -> Content) {
        self.title = title
        self.isExpanded = isExpanded
        self.content = content()
    }

    //
    var body: some View {
        HStack {
            VStack() { // to show content below title
                ExpandableListNameView(title: title, isExpanded: isExpanded)
                if isExpanded {
                    content
                }
            }
        }
                .contentShape(Rectangle()) // clickable all shape
                .padding(.vertical, 2)
    }
}
