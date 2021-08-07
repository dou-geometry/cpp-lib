/*     JROFI Öl=Wasser Interface behaviour simulation
 *     Copyright (C) 2021 Dou-geometry
 * 
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
 * Structure:
 *      Öl
 *    Wasser
 *
 * Forces: (negative downward, positive upward)
 *   - Gravity   (downward)
 *   - Floataion (upward)
 *   - Existence-Difference Acceleration
 */

#include"../../lib/dou/sys.hh"

int main() {
    auto g=[](const d::dou::compact::mono<double, 2, 2, true>& m) {
        return -9.80665;
    };
    auto buoyant = [](const d::dou::compact::mono<double, 2, 2, true>& m) {
        return 1;
    };
    auto combinedForce = [g, buoyant](const d::dou::compact::mono<double, 2, 2, true>& m) {
        return g(m)+buoyant(m);
    };
    return 0;
}
