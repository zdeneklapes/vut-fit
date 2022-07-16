//
//  iza_projectApp.swift
//  Shared
//
//  Created by Zdeněk Lapeš on 4/15/22.
//

import SwiftUI
import Firebase

@main
struct iza_projectApp: App {
    init() {
        FirebaseApp.configure()
    }

    var body: some Scene {
        WindowGroup {
            AppTabNavigationView()
        }
    }
}
