//
//  Month.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/28/22.
//

import Foundation

func getMonth(num: Int) -> String {
    switch num {
    case 1:return "January"
    case 2: return "February"
    case 3: return "March"
    case 4: return "April"
    case 5: return "May"
    case 6: return "June"
    case 7: return "July"
    case 8: return "August"
    case 9: return "September"
    case 10:return "October"
    case 11:return "November"
    case 12:return "December"
    default: return ""
    }
}
