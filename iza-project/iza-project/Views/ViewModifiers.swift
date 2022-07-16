//
//  ExpandableListViewModifiers.swift
//  iza-project
//
//  Created by Zdeněk Lapeš on 5/28/22.
//

import Foundation
import SwiftUI


//
struct TabItem: ViewModifier {
    var name: String
    var icon: String
    var tagNum: Tab

    func body(content: Content) -> some View {
        content
            .tabItem() { Label(name, systemImage: icon) }
            .tag(tagNum)
    }
}

// 
struct ListTextViewModifier: ViewModifier {
    func body(content: Content) -> some View {
        content
            .font(.headline)
            .padding(.leading)
    }
}

struct ListImageViewModifier: ViewModifier {
    func body(content: Content) -> some View {
        content
            .font(.system(size: 20, weight: .thin))
            .padding(.trailing)
    }
}

struct ScrollCell: ViewModifier {
    func body(content: Content) -> some View {
        Group {
            content
            Divider()
        }
    }
}

// 
struct StockInfoAttributeDescModifier: ViewModifier {
    func body(content: Content) -> some View {
        content
            .font(.caption).foregroundColor(.black)
    }
}

struct StockInfoAttributeValueModifier: ViewModifier {
    func body(content: Content) -> some View {
        content
            .font(.caption).foregroundColor(.blue)
    }
}

//
struct TextEditModifier: ViewModifier {
    let font = Font.system(.caption).weight(.bold)
    
    func body(content: Content) -> some View {
        content
            .font(font)
            .foregroundColor(Color.blue)
            .padding(5)
            .border(Color.blue, width: 2)
            .cornerRadius(5)
    }
}

//
struct WatchlistEditModifier: ViewModifier {
    func body(content: Content) -> some View {
        content
            .padding(10)
            .cornerRadius(8)
    }
}

//
struct SearchViewTextfieldViewModifier : ViewModifier {
    func body(content: Content) -> some View {
        content
                .padding(.all, 10)
                .overlay(Rectangle().frame(height: 2).padding(.top, 35))
                .foregroundColor(.blue)
    }
}

struct SearchStockResultViewModifier : ViewModifier {
    func body(content: Content) -> some View {
        content
            .buttonStyle(PlainButtonStyle())
            .padding(.all, 5)
    }
}

