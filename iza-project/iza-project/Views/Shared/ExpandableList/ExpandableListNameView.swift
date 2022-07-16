//
//  E.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/29/22.
//

import SwiftUI

struct ExpandableListNameView: View {
    var title: String
    let isExpanded: Bool

    //
    var body: some View {
        HStack {
            Text(title).modifier(ListTextViewModifier())
            Spacer()
            Image(systemName: isExpanded ? "chevron.up" : "chevron.down").modifier(ListImageViewModifier())
        }
    }
}
